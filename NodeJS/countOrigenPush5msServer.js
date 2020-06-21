// https://masaki-okuyama.github.io/DeadlineCountdown/
// v12.8.0
/*
  memo配列にpushで配列を使うと配列の先頭の要素が追加しようとしたら配列になる

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

var count=0;
var allHistorys=[];           //全ての履歴(Struct)を入れる配列
var flag_newhtml=true;        //直近に来たHTMLが履歴にあるかのフラグ
var newhtmlNum;               //新しく生成したStructのインスタンスが入っているallHistorysの番号
var limitByte=410*1000*0.02;  //HTML作成の時間で送ることができるByte数。(作成にかかる時間*速さ)
                              //中間審査では3G(410KBPS)なので410*1000*0.02
const headerSize=31;
var addtionByte=0;

limitByte=2000;              //テスト用にlimitByteに代入
                             //最初のjsまでなら20kぐらい、cssのみの大きさは3406
                             //20msでcssをプッシュしきれないようにするには3400*(1/0.02)/1000=170kBps

//limitByte=3450;           //cssまで全部プッシュできる
limitByte=618000;            

console.log("top:電大＿countPush5msServer");
console.log("テスト開始");

console.log("limitByteは"+limitByte);

//1番目の要素を削除する
// var items = ['リンゴ', 'メロン', 'イチゴ', 'スイカ'];
// var items=[];
// var head=['大根','人参']

// items.push('リンゴ');
// items.push('メロン');
// items.push('イチゴ');
// items.push('スイカ');

// console.log( items );
// items.unshift(items[2]);
// console.log( items )
// items.splice( 3, 1 )
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
struct=function Struct(html){
  this.html=html;       //リクエストされたHTML
  this.historys=[];     //そのHTMLを参照したことで、要求されたと思われるHTML上のパス  
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
    if(allHistorys[newhtmlNum].historys[i].slice(-1*extention.length)==extention){      //拡張子が一致
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
  var heads=[];
  var extentionCount=0;

  for(i=0;i<allHistorys[newhtmlNum].historys.length;i++){
    if(allHistorys[newhtmlNum].historys[i].slice(-1*extention.length)==extention){      //拡張子が一致
        // console.log("拡張子が一致しました");
        // console.log(allHistorys[newhtmlNum].historys[i]+"の判定中");

        heads.push(allHistorys[newhtmlNum].historys[i]);
        extentionCount++;
        moveAt(allHistorys[newhtmlNum].historys,i,0)  //挿入先が元の位置より常にまだからiに影響なし
    }
  }

  allHistorys[newhtmlNum].historys.splice(0,extentionCount);  //履歴と逆順になった先頭の群を削除
  allHistorys[newhtmlNum].historys=heads.concat(allHistorys[newhtmlNum].historys);
  return ;                                    
}


/*
  Explanation:allHistorysに入っているものをHTMLごとに出力するテスト用関数
*/
function  logAllHistorys(){
  console.log("allHistorys[i].historys.length:"+allHistorys[0].historys.length);

  for(i=0;i<allHistorys.length;i++){
    console.log("HTML"+allHistorys[i].html);
    for(j=0;j<allHistorys[i].historys.length;j++){
      console.log(allHistorys[i].historys[j]);
    }
  }
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
        //console.log(relativePath+'をプッシュしました');
    });
  return;
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

          if(count<4){
            extentionSort('js');
            extentionSort('css');
            console.log("ソートしました");
            count++;
          }
          // else
          //   logAllHistorys();
        },1000);
      } 
    });
  }
  else {
    relativePath = headers[':path'];   //リクエストがあったファイルのurl
  }

  var absolutePath = __dirname + relativePath;

  // console.log("相対パス"+headers[':path']);
  // console.log("絶対パス"+absolutePath);

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

  
  console.log("履歴判定に入ります");

  if(allHistorys.length==0){            //サーバ立ててから初めての要求
    allHistorys.push(new struct(relativePath));
    newhtmlNum=allHistorys.length-1;    //配列は0番目から数えるため
    ///////////////////////(1)でHTML送信するならここにもか？//////////////////////
  }else{
    for(i=0;i<allHistorys.length;i++){  //最初の時は長さが0なので入れないため上で追加
    // console.log(allHistorys.length);
      console.log("allHistorysの長さは"+allHistorys.length);
      console.log("相対パス"+relativePath);
      console.log("allHistorys["+i+"].htmlは"+allHistorys[i].html);
      if(allHistorys[i].html==relativePath){
        console.log("このHTMLは既に履歴にあります");
        flag_newhtml=false;
                                                            //CSSなどファイル別プッシュならここに入れる

        for(j=0;j<allHistorys[i].historys.length;j++){      //履歴を全プッシュ

          addtionByte = addtionByte + getFileSize(allHistorys[i].historys[j]);  //プッシュ予定のファイルの合計
          if(addtionByte<limitByte){
            // console.log(allHistorys[i].historys[j]+"をaddtionalByteに追加しました");
            console.log(allHistorys[i].historys[j]+"の大きさ:"+getFileSize(allHistorys[i].historys[j]));
            console.log("現在のaddtionByte:"+addtionByte);

            push(stream,allHistorys[i].historys[j]);
          }else{
            console.log(limitByte+"を超えるため"+allHistorys[i].historys[j]+"をプッシュしませんでした");
            console.log("addtionByte:"+addtionByte);
            addtionByte=0;  //次のプッシュに備えプッシュ予定のファイルサイズの合計をリセットしbreak;
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

  // fs.readFile(absolutePath, function(err, data) {
  //   if (err) {
  //     // エラー時の応答
  //     console.log("readFileエラーです");
  //   } else{
  //       // console.log("5msカウント開始");
  //       // setTimeout(function (){
  //       //   // stream.end(data);
  //       //   stream.end(data,function(){console.log("HTMLを遅らせて返しました");});
  //       //   // console.log("HTMLを送信したよ！");
  //       //   // console.log("HTML送信時のaddtionByte："+ addtionByte);

  //       //   // console.log("//////////ソート前///////////");
  //       //   // logAllHistorys();

  //       //   // console.log("//////////ソート後///////////");
  //       //   // logAllHistorys();
  //       // },5);

  //       if(count<4){
  //         // extentionSort('js');
  //         // extentionSort('css');
         
  //         prioritySort();
  //         extentionSort('js');
  //         priorityExtetionSort('css',256);
  //         console.log("ソートしました");
  //         count++;
  //       }
  //       else
  //         logAllHistorys();
  //       // setTimeout(function (){
  //       // stream.end(data);
  //       // console.log("HTMLの送信を遅らせたよ！");
  //       // // console.log("HTML送信時のaddtionByte："+ addtionByte);

  //       // console.log("//////////ソート前///////////");
  //       // logAllHistorys();

  //       // // reverseSort('png');
  //       // // reverseSort('js');
  //       // // reverseSort('css');

  //       // extentionSort('png');
  //       // extentionSort('js');
  //       // extentionSort('css');

  //       // console.log("//////////ソート後///////////");
  //       // logAllHistorys();
  //       // },20);
  //   } 
  // });

}else{              //HTML以外の要求
    // console.log("historysに保存します");
    // console.log("newhtmlnumは"+newhtmlNum);
    if(flag_newhtml==true)  //履歴にないHTMLによる要求だったら、パスをhistorysに追加
      allHistorys[newhtmlNum].historys.push(relativePath);


    fs.readFile(absolutePath, function(err, data) {
    if (err) {
      // エラー時の応答
      console.log("readFileエラーです:"+absolutePath);
    }else {
      // console.log("ファイルを読み込みました");
      // sleep(5000);
      // if(absolutePath.slice(-3)=="css")
       stream.end(data); //コンテンツを書き出す
      // stream.end(data,function(){console.log(relativePath+"を返しました");});
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

}); //serveron終了


server.on('error', (err) => console.error(err));
server.on('socketError', (err) => console.error(err));



server.listen(3000, (err) => {
  console.log('countServerAllpush running at https://localhost:3000');
  if (err) {
    console.error(err);
    return
  }
});