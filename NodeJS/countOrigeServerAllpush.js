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
var allHistorys=[];     //全ての履歴(Struct)を入れる配列
var flag_newhtml=true;  //直前に来たHTMLが履歴にあるかのフラグ
var newhtmlNum;         //新しく生成したStructのインスタンスが入っているallHistorysの番号

console.log("top:countServerAllpush");
console.log("通常アクセス");


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


//AllPushでは使わないかも
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


//AllPushでは使わないかも
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
  First:PushPromiseを送信する
  Second:リクエストされたパス
  Explanation:リクエストされたパスをサーバ上のパスに変換し、そのファイルをプッシュする 
*/
function push(stream,relativePath){
  // console.log("push関数に入りました。");

  var absolutePath = __dirname + relativePath;
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
          // logAllHistorys();
        },1000);
      } 
    });
  }
  else {
    relativePath = headers[':path'];   //リクエストがあったファイルのurl
  }

  var absolutePath = __dirname + relativePath;

  console.log("相対パス"+headers[':path']);
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

////////////////////AllPushはHTMLどこで送信するのか、先行研究見てみよう(とりあえず20ms待つ必要あるのか？)/////////////////////

  // fs.readFile(absolutePath, function(err, data) {
  //   if (err) {
  //     // エラー時の応答
  //     console.log("readFileエラーです");
  //   } else{      
  //     stream.end(data);
  //   } 
  // });

  console.log("履歴判定に入ります");

  if(allHistorys.length==0){            //サーバ立ててから初めての要求
    allHistorys.push(new struct(relativePath));
    newhtmlNum=allHistorys.length-1;    //配列は0番目から数えるため
  }else{
    for(i=0;i<allHistorys.length;i++){  //最初の時は長さが0なので入れないため上で追加
    // console.log(allHistorys.length);
      console.log("allHistorysの長さは"+allHistorys.length);
      console.log("相対パス"+relativePath);
      console.log("allHistorys["+i+"].htmlは"+allHistorys[i].html);
      if(allHistorys[i].html==relativePath){
        console.log("このHTMLは既に履歴にあります");
        flag_newhtml=false;

        for(j=0;j<allHistorys[i].historys.length;j++){      //履歴を全プッシュ
          // if((allHistorys[i].historys[j].slice(-2)=="js")||(allHistorys[i].historys[j].slice(-3)=="css"))
            push(stream,allHistorys[i].historys[j]);
        }
        break;
      }else if(i==allHistorys.length-1){   //全部見終わってもHTML履歴存在せず
        allHistorys.push(new struct(relativePath));
        flag_newhtml=true;
        newhtmlNum=allHistorys.length-1;  //配列は0番目から数えるため
        console.log("履歴に新しくHTMLを追加しました。");
        break;
        //履歴作らなきゃ
      }
    }
  }

  // fs.readFile(absolutePath, function(err, data) {
  //   if (err) {
  //     // エラー時の応答
  //     console.log("readFileエラーです");
  //   } else{
  //       console.log("HTMLを読み込みました");
  //       console.log("5msカウント開始");
  //       // stream.end(data);
  //       setTimeout(function (){
  //       stream.end(data,function(){
  //         console.log("HTMLを遅らせて返しました");});
  //         // logAllHistorys();
  //       // console.log("HTMLの送信を遅らせたよ！");
  //       },5);
  //   } 
  // });

}else{              //履歴にないhtmlからの要求
  if(flag_newhtml==true){  //履歴にないHTMLによる要求だったら、パスをhistorysに追加
    allHistorys[newhtmlNum].historys.push(relativePath);
    // console.log("historysに保存します");
    // console.log("newhtmlnumは"+newhtmlNum);
  }
    
  fs.readFile(absolutePath, function(err, data) {
    if (err) {
      // エラー時の応答
      console.log("readFileエラーです");
    }
    else {
      // console.log("ファイルを読み込みました");
      // sleep(5000);
      // stream.end(data); //コンテンツを書き出す 
      stream.end(data)
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

});


server.on('error', (err) => console.error(err));
server.on('socketError', (err) => console.error(err));



server.listen(3000, (err) => {
  console.log('countServerAllpush running at https://localhost:3000');
  if (err) {
    console.error(err);
    return
  }
});
