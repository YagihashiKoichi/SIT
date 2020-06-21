// https://masaki-okuyama.github.io/DeadlineCountdown/
// リモートから編集したよ
// v12.8.0
//2019/11/04：最初のjsが来たら残りのjsを全プッシュするけれど、プッシュの段階で一部のjsを遅れていたとしてもそうするのか？
/*
  memo配列にpushで配列を使うと配列の先頭の要素が追加しようとしたら配列になる

  注意点
  HTMLは20ms遅らせる必要があるのか

  問題点
  AllPush:先にソケットに全部入れる必要がある。20msで遅らせない。
  cssPush:データは圧縮して送るのが一般的。
          ->とりあえず無視
  cssPush:取得するファイルサイズはファイル単体のもの。headerなどは考慮されていない。
          ->headerの大きさは固定なので受信側で見て考慮に入れるようにする

  20ms:他の送信に影響を与えないように？ソートをHTML送信後にやっているけれど3回目かしかソートしているのを使えない
       1回目はHTML送信した時点で履歴なし、2回目はHTMLを送信した時点で既にプッシュしているため
       ソートしているタイミングで要求きたらまずいかな？ 
       それ以前にHTML送信時に毎回ソートしている。

  20ms:画像やフォントなどは拡張子が複数存在するため、引数が1つのextentionSort()では厳しいか？
       ->ソートするのはcssとjsだけで良い

        画像の拡張子:jpg,jpeg,JPG,JPEG,
                  png
                  gif
        引数の個数が異なる関数をもう一個作成や、配列などで対応はできたかもしれないけれど
      

  改良点(未)
  pushcss
    cssにおけるプッシュ量制限の
    最初のjsが来た時のプッシュに未対応

  20ms
    (ソートの拡張子は配列でも良いかも)
    ソート結果を用いたプッシュ
    header考慮
    上記を含め、問題点と同じ

  改良点(済)
  '/'と'index.html'を区別して保存しているけれど、変換したやつ(relativePath)で判断すれば良いのでは？
  注意点
  今全プッシュだからCSS送信だけプッシュはHTML同様に最後の3文字を見ること
  1ページにHTMLが複数あった場合の挙動はよくわからない。HTMLに書いてあるものの要求が全てきてから、他のHTML要求が来る前提で作成。

*/


const http2 = require('http2');
const fs = require('fs');
const mime = require('mime');
const { HTTP2_HEADER_PATH } = http2.constants;

// console.time('getreq');


var cssCount=0;
var jsCount=0;
var pngCount=0;
var jpgCount=0;
var svgCount=0;
var woff2Count=0;
var woffCount=0;
var otfCount=0;



var count=0;
var allHistorys=[];           //全ての履歴(Struct)を入れる配列
var flag_newhtml=true;        //直近に来たHTMLが履歴にあるかのフラグ
var newhtmlNum;               //新しく生成したStructのインスタンスが入っているallHistorysの番号
var pushOverNum;              //初期値をどうするか、全プッシュできた時初期値と更新のタイミングが大事
var latesthtmlNum;

var limitByte=410*1000*0.02;  //HTML作成の時間で送ることができるByte数。(作成にかかる時間*速さ)
                              //中間審査では3G(410KBPS)なので410*1000*0.02

const headerSize=31;
var addtionByte=0;            //pushOverNumもそうだがこれはユーザごとにあるものなので今回は複数同時アクセスを想定していない
//400kb/sだとcssのPushに7.645msかかる
limitByte=2000;              //テスト用にlimitByteに代入
                             //最初のjsまでなら20kぐらい、cssのみの大きさは3406
                             //20msでcssをプッシュしきれないようにするには3400*(1/0.02)/1000=170kBps
// limitByte=3450;           //cssまで全部プッシュできる

limitByte=618000;            //jsの途中

console.log("top:countPushcssServer");
console.log("テスト開始");

console.log("limitByteは"+limitByte);

//1番目の要素を削除する
var items = ['リンゴ', 'メロン', 'イチゴ', 'スイカ'];
// var items=[];
// var head=['大根','人参']

// items.push('リンゴ');
// items.push('メロン');
// items.push('イチゴ');
// items.push('スイカ');

// console.log( items );
// moveAt(items,1,3);
// console.log( items );
// items.unshift(items[2]);
// console.log( items );
// items.splice( 3, 1);

// console.log( items );
// items=head.concat(items);

// for(i=0;i<items.length;i++){
//   console.log(i+":"+items[i]);
// }


// var extention="css";
// var length=-1*extention.length;
// console.log("sliceする数:"+length);
// var fail="experiment.css";
// console.log("sliceした結果:"+fail.slice(-1*extention.length))

// var extention="css";
// console.log("extentionの文字数："+extention.length);

// var path="/Users/yagihashikoichi/Desktop/experiment/MyPortfolio/CSS/styles.css"
// getFileSize(path);
// var st = fs.statSync("/Users/yagihashikoichi/Desktop/experiment/MyPortfolio/CSS/styles.css");

// console.log("ファイルサイズは："+st.size+"Byte");
// console.log("headerを含めると："+(st.size+headerSize)+"Byte");



// /Users/yagihashikoichi/Desktop/experiment/countPush20ms/DeadlineCountdown 

// console.log("関数使用" + getFileSize('/assets/css/style.css'));

console.log("テスト終了");


/*
  Argment:リクエストされたHTMLのパス
  Explanation:インスタンスを作ることでCの構造体のように振る舞う。
*/
struct=function newStruct(html){
  this.html=html;       //リクエストされたHTML
  this.historys=[];     //そのHTMLを参照したことで、要求されたと思われるHTML上のパス
  this.cssLength=0;
}

fileInfo=function newFileInfo(reference,priority){
  this.reference=reference;
  this.priority=priority;
}


//関数にするか迷い中
function addHistory(history){
}

//関数にするか迷い中
function readFile(absolutePath) {
  // body...
}

/*
  Argment:サイズを知りたいファイルのHTML上のパス
  Explanation:引数で受け取ったパスのファイルの大きさ+headerをByte単位で返す
*/
function getFileSize(relativePath) {
  // console.log("getFileSize関数に入りました");
  // console.log("サイズを知りたいファイルの絶対パス:"+absolutePath);
  var totalSize;
  var absolutePath = __dirname + relativePath;

  var stat = fs.statSync(absolutePath);
  // console.log("ファイルサイズは："+stat.size+"Byte");
  totalSize=stat.size+headerSize;

  return totalSize;
}


/*
  First argment:要素の場所を変更したい配列
  Second argment:場所を変更したい要素の番号
  Third argment:変更先の場所の番号
  Return:要素の場所を変えた配列
  Explanation:第二引数で受け取った番号にある要素を第三引数で受け取った番号にある場所に移動し、移動先より後ろの
              要素は移動元まで詰めた状態にする。
*/
function moveAt(array, index, at) {
    if (index === at || index > array.length -1 || at > array.length - 1) {
      return array;
    }

    const value = array[index];
    const tail = array.slice(index + 1);

    array.splice(index);

    Array.prototype.push.apply(array, tail);

    array.splice(at, 0, value);

    return array;
}



/*
  問題点
    newhtmlNumだと存在するものが来た時に更新されていないから問題
    ->flag_newhtmlとの併用か？
    履歴順にするなら画像,js,cssの順で後ろから見て前に移していくのが良いのでは？
    ->for文は++では--にするか、length-i？みたいな感じにすれば良いと思う

  注意点
    sliceに使う引数(どこを何文字)は'extention.length'で出せば良い
    
    先頭に追加：unshift()
    削除：array.splice(1, 1)
        array.splice(配列の何個目か, 第一引数のとこから何個か)
    置換:arr.splice(index, 0, value);
    挿入:arr.splice(index, 1, value);

  代案
    ファイル読み込みの時点でrequire('file-type')の機能を使うことで拡張子を取得できる。
    そこでhistorysの下にインスタンス拡張子を含むインスタンを作成する。
    ->HTML上とディレクトリが対応しているんだから、拡張子今のままでよくない？
*/

/*
  Argment:historysの先頭に持っていきたい拡張子
  Explanation:引数で受け取った拡張子のファイルをhistorysの先頭に持っていく(引数となった拡張子は履歴と逆順になる)

*/
function  reverseSort(extention){
  console.log("拡張子"+extention+"でsort関数に入りました");
  console.log("newhtmlNum:"+newhtmlNum);
  for(i=0;i<allHistorys[newhtmlNum].historys.length;i++){
    if(allHistorys[newhtmlNum].historys[i].reference.slice(-1*extention.length)==extention){      //拡張子が一致
        // console.log("拡張子が一致しました");
        // console.log(allHistorys[newhtmlNum].historys[i]+"の判定中");
        moveAt(allHistorys[newhtmlNum].historys,i,0);
        // allHistorys[newhtmlNum].historys.unshift(allHistorys[newhtmlNum].historys[i]);  //先頭に同じものを追加
        // // i++;                                                  //先頭に追加したことでずれたから  
        // allHistorys[newhtmlNum].historys.splice(i,1);
        // console.log("sort途中経過");
        // logAllHistorys();         
    }
  }
  return ;                                    
}

/*
  Argment:historysの先頭に持っていきたい拡張子
  Explanation:引数で受け取った拡張子のファイルを履歴順を維持してhistorysの先頭に持っていく
*/
function  extentionSort(extention){
  var heads=[];         //ここに入れたのものを後から先頭にくっつける
  var extentionCount=0;

  for(i=0;i<allHistorys[newhtmlNum].historys.length;i++){
    if(allHistorys[newhtmlNum].historys[i].reference.slice(-1*extention.length)==extention){      //拡張子が一致
        // console.log("拡張子が一致しました");
        // console.log(allHistorys[newhtmlNum].historys[i]+"の判定中");

        heads.push(allHistorys[newhtmlNum].historys[i]);
        extentionCount++;
        moveAt(allHistorys[newhtmlNum].historys,i,0)  //挿入先が元の位置より常にまだからiに影響なし
    }
  }

  if(extention=='css')     //cssのみプッシュする際にcssが何個かあるかわかるように
    allHistorys[newhtmlNum].cssLength=extentionCount;

  allHistorys[newhtmlNum].historys.splice(0,extentionCount);  //履歴と逆順になった先頭の群を削除
  allHistorys[newhtmlNum].historys=heads.concat(allHistorys[newhtmlNum].historys);
  return ;                                    
}

/*
  Explanation:weight(priority)の降順に要求順を維持して、並べ替える
*/
function  prioritySort(){
  var alterHistory=[];
  var topPriority;
  for(i=0;i<allHistorys[newhtmlNum].historys.length-1;i++){
    for(j=allHistorys[newhtmlNum].historys.length-1;i<j;j--){
      if(allHistorys[newhtmlNum].historys[j-1].priority<allHistorys[newhtmlNum].historys[j].priority){
        alterHistory[0]=allHistorys[newhtmlNum].historys[j-1];
        allHistorys[newhtmlNum].historys[j-1]=allHistorys[newhtmlNum].historys[j];
        allHistorys[newhtmlNum].historys[j]=alterHistory[0];
      }
    }
  }
}

function  priorityExtetionSort(extention,topPriority){
  var heads=[];         //ここに入れたのものを後から先頭にくっつける
  var extentionCount=0;

  for(i=0;i<allHistorys[newhtmlNum].historys.length;i++){
    if(allHistorys[newhtmlNum].historys[i].reference.slice(-1*extention.length)==extention&&(allHistorys[newhtmlNum].historys[i].priority==topPriority)){      //拡張子が一致
        // console.log("拡張子が一致しました");
        // console.log(allHistorys[newhtmlNum].historys[i]+"の判定中");

        heads.push(allHistorys[newhtmlNum].historys[i]);
        extentionCount++;
        moveAt(allHistorys[newhtmlNum].historys,i,0)  //挿入先が元の位置より常にまだからiに影響なし
    }
  }

  if(extention=='css')     //cssのみプッシュする際にcssが何個かあるかわかるように
    allHistorys[newhtmlNum].cssLength=extentionCount;

  allHistorys[newhtmlNum].historys.splice(0,extentionCount);  //履歴と逆順になった先頭の群を削除
  allHistorys[newhtmlNum].historys=heads.concat(allHistorys[newhtmlNum].historys);
  return ;                 


}

// function  fontThirdPrioritySort(){
//     for(i=0;i<allHistorys[newhtmlNum].historys.length-1;i++){
//       if((allHistorys[newhtml].historys[i].reference.slice(-3)=="otf")||(allHistorys[newhtml].historys[i].reference.slice(-4)=="woff")||(allHistorys[newhtml].historys[i].reference.slice(-5)=="woff2")){
//         moveAt(allHistorys[newhtml].historys[i],i,0)//あとで第三引数をjsの終わりに変えること
//       }
//     }
// }

function getPriorityLength(){



}


/*
  Explanation:allHistorysに入っているものをHTMLごとに出力するテスト用関数
*/
function  logAllHistorys(){
  console.log("履歴の状況です。");
  var prioritySize=0;
  var cssAndjsSize=0;
  var unnecessaryCssSize=0;
  console.log("allHistorys["+i+"].historys.length:"+allHistorys[0].historys.length);

  for(i=0;i<allHistorys.length;i++){
    console.log("HTML"+allHistorys[i].html);
    for(j=0;j<allHistorys[i].historys.length;j++){
      console.log(allHistorys[i].historys[j].reference + ":"+allHistorys[i].historys[j].priority);

      if(allHistorys[i].historys[j].reference.slice(-2)=="js"){
        cssAndjsSize = cssAndjsSize + getFileSize(allHistorys[i].historys[j].reference);
        prioritySize = prioritySize + getFileSize(allHistorys[i].historys[j].reference);
        // console.log("1に入りました");
      }
      else if((allHistorys[i].historys[j].reference.slice(-3)=="css")&&(allHistorys[i].historys[j].priority==256)){
        prioritySize = prioritySize + getFileSize(allHistorys[i].historys[j].reference);
        cssAndjsSize = cssAndjsSize + getFileSize(allHistorys[i].historys[j].reference);

        // console.log("2に入りました");
      }
      else if((allHistorys[i].historys[j].reference.slice(-3)=="css")&&(allHistorys[i].historys[j].priority!=256)){
        cssAndjsSize = cssAndjsSize + getFileSize(allHistorys[i].historys[j].reference);
        unnecessaryCssSize = unnecessaryCssSize + getFileSize(allHistorys[i].historys[j].reference);
        // console.log("3に入りました");   
      }
    }
  }
  console.log("prioritySize:" + prioritySize);
  console.log("cssAndjsSize:" + cssAndjsSize);
  console.log("unnecessaryCssSize:" + unnecessaryCssSize);

  return  ;
}


/*
  First argment:PushPromiseを送信する
  Second:リクエストされたパス
  Explanation:リクエストされたパスをサーバ上のパスに変換し、そのファイルをプッシュする 
*/
function push(stream,relativePath){
  // console.log("push関数に入りました。");
                                                    //どこに入れようか、そしてフラグはどうする
  var absolutePath = __dirname + relativePath;
  // limitByte = limitByte - getFileSize(absolutePath);  //limitbyteによる判定がない

  stream.pushStream({ ':path': relativePath }, (err, pushStream, headers) => {
      if (err) throw err;
      pushStream.respond({
        'content-type': mime.getType(relativePath),
        'content-encoding': 'identity',
        ':status': 200,
      });

      fs.readFile(absolutePath, function(err, data) {
        if (err) {
          console.log("readFileエラーです:"+relativePath);
        }
        else {
          // console.log(relativePath+"を読み込みました");
          // pushStream.end(data);
          pushStream.end(data,function(){console.log(relativePath+"をプッシュしました");});
        }
      });   
        // console.log(relativePath+'をプッシュしました');
    });
  return;
}



function  extentionNumber(path){
  if(path.slice(3)=="css")
    cssCount++;
  else  if(path.slice(-2)=="js")
    jsCount++;
  else  if(path.slice(-3)=="png")
    pngCount++;
  else  if(path.slice(-3)=="jpg")
    jpgCount++;
  else  if(path.slice(-3)=="svg")
    svgCount++;
  else  if(path.slice(-5)=="woff2")
    woff2Count++;
  else  if(path.slice(-4)=="woff")
    woffCount++;
  else  if(path.slice(-3)=="otf")
    otfCount++;
}



const server = http2.createSecureServer({
  key: fs.readFileSync('localhost-privkey.pem'),
  cert: fs.readFileSync('localhost-cert.pem')
});
console.log("afterServer");


//成功
server.on('stream', (stream, headers) => {
  // console.log("serveron");
  // stream is a Duplex
  // console.log("serveronに入りました");
  
  // count++;

  stream.respond({
    'content-type': mime.getType(headers[':path']),
    'content-encoding': 'identity',
    ':status': 200,
  });
   

  //特定のファイル要求が来た時用
  // if(headers[':path']=="/"){
  //   console.log("履歴一覧を表示します");
  //   for(i=0;i<history.length;i++){
  //      console.log(history[i]);
  //   }
   
  // }

  // console.timeLog('getreq',headers[':path']);
  
  if (headers[':path']== '/') {   //3000のポートに接続要求があったとき
    relativePath = '/index.html';
    console.log("\n\n");
    console.log("1000msカウント開始");
    fs.readFile(__dirname + relativePath, function(err, data) {
      if (err) {
        // エラー時の応答
        console.log("readFileエラーです");
      } else{
          // console.log("5msカウント開始");
          setTimeout(function (){
            stream.end(data,function(){console.log("HTMLを遅らせて返しました");});

           if(allHistorys[0].historys.length!=0){
              allHistorys[0].historys[0].priority=256;
              // allHistorys[0].historys[2].priority=256;
              console.log(allHistorys[0].historys[0].reference + "のpriorityを256にしました");
              for(k=0;k<allHistorys[0].historys.length;k++){
                if(allHistorys[0].historys[k].reference=='/common/css/jquery.bxslider.css'){
                  allHistorys[0].historys[k].priority=256;
                  console.log(allHistorys[0].historys[k].reference + "のpriorityを256にしました");
                } else if(allHistorys[0].historys[k].reference=='/common/libs/imagesloaded.pkgd.min.js'){
                  allHistorys[0].historys[k].priority=256;
                  console.log(allHistorys[0].historys[k].reference + "のpriorityを256にしました");
                  break;
                }
              }


             // console.log(allHistorys[0].historys[2].reference + "のpriorityを256にしました");
           }

          if(count<4){
            prioritySort();
            priorityExtetionSort('js',220);
            priorityExtetionSort('css',256);
            console.log("ソートしました");
            count++;
          }


          // logAllHistorys();
          

            // // console.log("//////////ソート後///////////");
           // // logAllHistorys();
         },1000);
    } 
  });
    // console.log(headers);
  }
  else {
    relativePath = headers[':path'];   //リクエストがあったファイルのurl
    // if(relativePath.slice(-3)=="css"){
    //   setTimeout(function (){
    //     console.log(relativePath+" time "+stream.state.weight);
    //   },2000);
    // }
    //Cssの優先度合をみる
    // if(relativePath.slice(-3)=="css")
    //   console.log(relativePath+"："+stream.state.weight);
    // else  if(relativePath.slice(-2)=="js")
    //   console.log(relativePath+"："+stream.state.weight);
  }

  var absolutePath = __dirname + relativePath;

  // console.log("相対パス"+headers[':path']);
  // console.log("絶対パス"+absolutePath);

  // console.log(headers[':priority']+" : "+headers[':path']);

  ////////////////////旧オートプッシュ始め////////////////////////////

  // if((absolutePath=='/Users/yagihashikoichi/Desktop/experiment/MyPortfolio/index.html')&&(history.length!=0)){

  //   for(i=0;i<history.length;i++){
  //     push(stream,history[i]);

  //   }

  //   i++;
  // }else if(absolutePath!='/Users/yagihashikoichi/Desktop/experiment/MyPortfolio/index.html'){
  //   history.push(relativePath);
  // }
 ////////////////////旧オートプッシュ終わり////////////////////////////
  


/*
  全プッシュは20ms待つ必要があるのか？
  プロキシだけれどHTMLの講更新があれば取りに行くから待ってみる。
  全プッシュを保証するなら、HTML送信が上の方にあるのは問題なのでは？
  でも、後にしても読み込み時間次第ではHTMLが最後になるという保証はないのではないか？

  結果：
  20ms待ち：全プッシュできた
  待たないで上の方：全プッシュできた
*/

////////////////////////////新オートプッシュ開始///////////////////////////////////////////

if(relativePath.slice(-4)=="html"){    //要求されたファイルがhtml
  
  addtionByte=0;  
  console.log("履歴判定に入ります");

  if(allHistorys.length==0){            //サーバ立ててから初めての要求(HTML)
    allHistorys.push(new struct(relativePath));
    newhtmlNum=allHistorys.length-1;    //配列は0番目から数えるため
    ///////////////////////(1)でHTML送信するならここにもか？//////////////////////
  }else{
    for(i=0;i<allHistorys.length;i++){  //最初の時は長さが0なので入れないため上で追加
      // console.log(allHistorys.length);
      // console.log("allHistorysの長さは"+allHistorys.length);
      // console.log("相対パス"+relativePath);
      // console.log("allHistorys["+i+"].htmlは"+allHistorys[i].html);
      if(allHistorys[i].html==relativePath){
        latesthtmlNum=i;                                    //要求が来た際にどのHTMLからの要求かを特定するのに使用
        // console.log("このHTMLは既に履歴にあります");
        // console.log("reference" + allHistorys[i].historys[0].reference);
        flag_newhtml=false;
                                                            //CSSなどファイル別プッシュならここに入れる

///////////優先してプッシュする条件をただのCSSから優先度の高いCSSに変更する必要あり////////////////////////////////////
        // console.log("cssの数:"+allHistorys[i].cssLength);

        // for(j=0;j<allHistorys[i].cssLength;j++){      //cssを全プッシュ
        //   addtionByte = addtionByte + getFileSize(allHistorys[i].historys[j].reference);  //プッシュ予定のファイルの合計
        //   push(stream,allHistorys[i].historys[j].reference);
        // }

         for(j=0;j<allHistorys[i].historys.length;j++){      //cssを全プッシュ
          if(allHistorys[i].historys[j].reference.slice(-5)=="woff2"){
            allHistorys[i].cssLength=j;       //実際はcssLengthではないがプッシュの続きだからとりあえず代入
            console.log(allHistorys[i].historys[j].reference + "をプッシュしませんでした");
            break;
          }
          // console.log(allHistorys[i].historys[j].reference + "ｊは"+j);
          addtionByte = addtionByte + getFileSize(allHistorys[i].historys[j].reference);  //プッシュ予定のファイルの合計
          push(stream,allHistorys[i].historys[j].reference);
        }




        //実験用:追加でプッシュしたいとき
        //push(stream,'/common/libs/jquery.rwdImageMaps.min.js');


        //console.log("css"+allHistorys[i].historys[j]+"の大きさ:"+getFileSize(allHistorys[i].historys[j]));
        // console.log("css全プッシュ後のaddtionByte:"+addtionByte);
        console.log("優先全プッシュ後のaddtionByte:"+addtionByte);

        for(j=allHistorys[i].cssLength;j<allHistorys[i].historys.length;j++){   //cssの次(js)からできるところまでプッシュ
          addtionByte = addtionByte + getFileSize(allHistorys[i].historys[j].reference);  //プッシュ予定のファイルの合計
          if(addtionByte<limitByte){
            // console.log(allHistorys[i].historys[j]+"をaddtionalByteに追加しました");
            console.log(allHistorys[i].historys[j]+"の大きさ:"+getFileSize(allHistorys[i].historys[j].reference));
            console.log("現在のaddtionByte:"+addtionByte);
            push(stream,allHistorys[i].historys[j].reference);
          }else{
            console.log(limitByte+"を超えるため"+allHistorys[i].historys[j].reference+"をプッシュしませんでした");
            console.log("addtionByte:"+addtionByte);

            pushOverNum=j;  //次の要求はこれを含んだ以降からくるであろう
            //addtionByte=0;  //次のプッシュに備えプッシュ予定のファイルサイズの合計をリセットしbreak;
            break;
          }
        }
        break;
      }else if(i==allHistorys.length-1){   //全部見終わってもHTML履歴存在せず
        allHistorys.push(new struct(relativePath));
        flag_newhtml=true;
        newhtmlNum=allHistorys.length-1;  //配列は0番目から数えるため
        console.log("履歴に新しくHTMLを追加しました。");
        break;
      }
    }
  }

  // fs.readFile(absolutePath, function(err, data) {
  //   if (err) {
  //     // エラー時の応答
  //     console.log("readFileエラーです");
  //   } else{      
  //     stream.end(data);
  //   } 
  // });

////////////////////////////////////////要求直後に移植：開始/////////////////////////////////////////////////////////
  // fs.readFile(absolutePath, function(err, data) {
  //   if (err) {
  //     // エラー時の応答
  //     console.log("readFileエラーです");
  //   } else{
        // console.log("5msカウント開始");
        // setTimeout(function (){
        // // stream.end(data);
        // stream.end(data,function(){console.log("HTMLを遅らせて返しました");});
        // // console.log("HTMLの送信を遅らせたよ！");
        // // console.log("HTML送信時のaddtionByte："+ addtionByte);

        // // console.log("//////////ソート前///////////");
        // // logAllHistorys();

        // // reverseSort('png');
        // // reverseSort('js');
        // // reverseSort('css');

        // //extentionSort('png');

        // if(allHistorys[0].historys.length!=0){
        //   allHistorys[0].historys[0].priority=256;
        //   console.log(allHistorys[0].historys[0].reference + "のpriorityを256にしました");
        // }

        // if(count<4){
        //   prioritySort();
        //   extentionSort('js');
        //   priorityExtetionSort('css',256);
        //   console.log("ソートしました");
        //   count++;
        // }
        // else
        //   logAllHistorys();
        

        // // console.log("//////////ソート後///////////");
        // // logAllHistorys();
        // },5);
  //   } 
  // });
/////////////////////////////////////////要求直後に移植：終了/////////////////////////////////////////////////////        


}else{              //HTML以外の要求
    // console.log("historysに保存します");
    // console.log("newhtmlnumは"+newhtmlNum);
    ////////////////////////////////////////////一回で配列にプッシュできているか怪しい
    if((headers[':path'].slice(-3)=="css")&&(stream.state.weight!=256)){
      console.log(headers[':path']+"："+" weight"+stream.state.weight);
      // console.log(headers)
      // console.log(stream);
    }else if((headers[':path'].slice(-2)=="js")&&(stream.state.weight!=220)){
      console.log(headers[':path']+"："+" weight"+stream.state.weight);
      // console.log(headers)
      // console.log(stream);
    }else if(headers[':path'].slice(-5)=="woff2"){
      console.log(headers[':path']+"："+" weight"+stream.state.weight);
      // console.log(headers)
      // console.log(stream);
    }

    if(flag_newhtml==true){  //履歴にないHTMLによる要求だったら、パスをhistorysに追加
      allHistorys[newhtmlNum].historys.push(new fileInfo(relativePath,stream.state.weight));
    }else{//////////////////追いプッシュ：ここを依存しているファイルをプッシュするように変更したい
      // if((relativePath==allHistorys[latesthtmlNum].historys[pushOverNum])&&(allHistorys[latesthtmlNum].historys[pushOverNum].slice(-2)=="js")){
      //   console.log("プッシュしきれなかったファイルの要求が来ました"+relativePath);
      //   while(true){
      //     pushOverNum++;
      //     // console.log();
      //     if(allHistorys[latesthtmlNum].historys[pushOverNum].slice(-2)!="js")
      //       break;
      //     push(stream,allHistorys[latesthtmlNum].historys[pushOverNum]);    
      //   }
      // }
    }
    
    fs.readFile(absolutePath, function(err, data) {
      if (err) {
        // エラー時の応答
        console.log("readFileエラーです");
      }
      // else if(absolutePath=='/Users/yagihashikoichi/Desktop/experiment/countPushcss/DeadlineCountdown/assets/css/yakuhanjp.css'){
      //   console.log("何もしまんせんでした");

      // }
      else {
        // console.log("ファイルを読み込みました");
        // // sleep(5000);
        // stream.end(data); //コンテンツを書き出す 
         stream.end(data);
        }
    });
    
}

////////////////////////////新オートプッシュ終了///////////////////////////////////////////






  // fs.readFile(absolutePath, function(err, data) {
  //   if (err) {
  //     // エラー時の応答
  //     console.log("readFileエラーです");

  //   } else if(absolutePath=='/Users/yagihashikoichi/Desktop/experiment/MyPortfolio/index.html'){
  //       setTimeout(function (){
  //       stream.end(data);
  //       console.log("HTMLの送信を遅らせたよ！");
  //       },20);
  //   } 

  //    else {
  //     // console.log("ファイルを読み込みました");
  //     // sleep(5000);
  //     stream.end(data); //コンテンツを書き出す 
  //     }
  // });

  // console.log("リクエスト数は"+count+"です。");

});   //serveron終了


server.on('error', (err) => console.error(err));
server.on('socketError', (err) => console.error(err));



server.listen(3000, (err) => {
  console.log('countPushPriority running at https://localhost:3000');
  if (err) {
    console.error(err);
    return
  }
});
