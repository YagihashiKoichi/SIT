const http2 = require('http2');
const fs = require('fs');
const mime = require('mime');
const { HTTP2_HEADER_PATH } = http2.constants;

var htmlCount=0;
var cssCount=0;
var jsCount=0;
var pngCount=0;
var jpgCount=0;
var svgCount=0;
var woff2Count=0;
var woffCount=0;
var otfCount=0;
var otherCount=0;

const headerSize=31;

console.time('getreq');

console.log("top:countHTTP2Server");
console.log("通常アクセス")
// console.log("HTML以外なにも返しません");
// console.log("開発機能を有効にしてアクセス")
const server = http2.createSecureServer({
  key: fs.readFileSync('localhost-privkey.pem'),
  cert: fs.readFileSync('localhost-cert.pem')
});
console.log("afterServer");


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

  Explanation:それぞれの拡張子の数をカウント
*/
function  extentionNumber(path){
  if(path.slice(-4)=="html")
    htmlCount++;
  else  if(path.slice(-3)=="css")
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
  else
    otherCount++;
}

/*
  First:要求されたファイルのパス
  Explanation:現在のファイルの数を出力
*/
function  getExtentionNumber(){
  console.log("htmlCount:"+ htmlCount);
  console.log("cssCount:" + cssCount);
  console.log("jsCount:"  + jsCount);
  console.log("pngCount:" + pngCount);
  console.log("jpgCount:" + jpgCount);
  console.log("svgCount:" + svgCount);
  console.log("woff2Count:" + woff2Count);
  console.log("woffCount:" + woffCount);
  console.log("otfCount:" + otfCount);
  console.log("otherCount:" + otherCount);
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

//成功
server.on('stream', (stream, headers) => {
  // stream is a Duplex
  // console.log("serveronに入りました");
  // console.log("server_onに入りました");

  stream.respond({
    'content-type': mime.getType(headers[':path']),
    'content-encoding': 'identity',
    ':status': 200,
  });

  // console.log("相対パス");
  // console.log(headers[':path']);
  console.timeLog('getreq',headers[':path']);

  // if(headers[':path']=="/common/images/recommend/inaba.jpg"){
  //   console.log("目的のデータの要求が来ました");
  // }

   if (headers[':path']== '/') {   //3000のポートに接続要求があったとき
    console.log("\n\n");
    relativePath = '/index.html'; 
    // console.log(headers[':path']+"："+" weight"+stream.state.weight+" ID:"+stream.id);
  }
  else {
    relativePath = headers[':path'];   //リクエストがあったファイルのurl
    // console.log(headers[':path']+"："+ getFileSize(headers[':path']));

    // if((headers[':path'].slice(-3)=="css")&&(stream.state.weight!=256)){
    //   console.log(headers[':path']+"："+" weight"+stream.state.weight);
    //   // console.log(headers)
    //   // console.log(stream);
    // }else if((headers[':path'].slice(-2)=="js")&&(stream.state.weight!=220)){
    //   console.log(headers[':path']+"："+" weight"+stream.state.weight);
    //   // console.log(headers)
    //   // console.log(stream);
    // }

    // if(relativePath=="/common/font/NotoSansJP-Regular.woff2"){
    //     console.log("目的の要求が来ました"+relativePath);
    // }

    // if(stream.state.weight==256)
    //   console.log(headers[':path']+"："+" weight"+stream.state.weight);

    // if(relativePath.slice(-3)=="css"){
    //   console.log(headers[':path']+"："+" weight"+stream.state.weight+" ID:"+stream.id);
    //   // console.log(headers)
    //   // console.log(stream);
    // }
    
  }

  // console.log(stream.state. sumDependencyWeight);
  // console.log(stream.state. streamDependency);

  var absolutePath = __dirname + relativePath;

  // extentionNumber(relativePath);
  // console.log("絶対パス");
  // console.log(absolutePath);

  //HTMLの場合はHTML作成時間(5ms)の遅延が入る
  //コメントをわかりやすくするため極端な書き方をしている
  if(absolutePath.slice(-4)=="html"){

  // push(stream,'/common/css/swipebox.css');
  // push(stream,'/common/css/jquery.bxslider.css');
  // push(stream,'/common/libs/jquery.easing.1.3.js');
  // push(stream,'/common/libs/jquery.timers.js');
  // push(stream,'/common/libs/jquery.tile.min.js');
  // push(stream,'/common/libs/matchMedia.js');
  // push(stream,'/common/libs/imagesloaded.pkgd.min.js');
  // push(stream,'/common/libs/jquery.rwdImageMaps.min.js');
  // push(stream,'/common/libs/jquery.swipebox.js');
  // push(stream,'/common/libs/jquery.flicksimple.js');
  // push(stream,'/common/libs/jquery.cookie.js');
  // push(stream,'/common/libs/jquery.lazyload.js');

  // push(stream,'/common/css/print.css');
  // push(stream,'/common/css/font.css');

  // push(stream,'/common/libs/jquery.bxslider.js');
  // push(stream,'/common/libs/jquery-1.11.3.min.js');

  // push(stream,'/common/css/common_sp.css');
  
  // push(stream,'/common/css/common_pc.css');
  // push(stream,'/common/css/style_pc.css');
  // push(stream,'/common/js/share.js');
  // push(stream,'/common/css/style_sp.css');

  // push(stream,'/common/font/NotoSansJP-Regular.woff2');
  // push(stream,'/common/font/NotoSansJP-Regular.woff');
  // push(stream,'/common/font/NotoSansJP-Regular.otf');

  fs.readFile(absolutePath, function(err, data) {
	    if (err) {
	      // エラー時の応答
	      console.log("readFileエラーです");
	    } else{
	        console.log("HTMLを読み込みました");
	        console.log("10msカウント開始");
	        // stream.end(data);
	        setTimeout(function (){
	        stream.end(data,function(){
	          console.timeLog('getreq',"HTMLを遅らせて返しました");});
	          // logAllHistorys();
	        // console.log("HTMLの送信を遅らせたよ！");
	        },10);
	    } 
 	});
  }else{
    fs.readFile(absolutePath, function(err, data) {
	    if (err) {
	      // エラー時の応答
        console.log("readFileエラーです");
	    }
      // else if(absolutePath==__dirname+'/common/css/print.css'){
      //   console.log("ファイル返さない:"+absolutePath);
      // }
      // else if(absolutePath==__dirname+'/common/css/common_sp.css'){
      //   console.log("ファイル返さない:"+absolutePath);
      // }
      // else if(absolutePath==__dirname+'/common/css/style_sp.css'){
      //   console.log("ファイル返さない:"+absolutePath);
      // }
      // else if(absolutePath==__dirname+'/sum.js'){
      //    setTimeout(function (){
      //     stream.end(data,function(){
      //       console.log("sum.jsを遅らせて返しました");});
      //       // logAllHistorys();
      //     // console.log("HTMLの送信を遅らせたよ！");
      //     },15000);
      // }

      // else if(absolutePath==__dirname+'/bigJS.js'){
      //    console.log("返さない");
      // }

      // else if(absolutePath==__dirname+'/common/font/NotoSansJP-Regular.woff2'){
      //   console.log("ファイル返さない:"+absolutePath);
      // }
      // else if(absolutePath==__dirname+'/common/font/NotoSansJP-Regular.woff'){
      //   console.log("ファイル返さない:"+absolutePath);
      // }
      // else if(absolutePath==__dirname+'/common/font/NotoSansJP-Regular.otf'){
      //   console.log("ファイル返さない:"+absolutePath);
      // }

      // else if(absolutePath.slice(-3)=="svg"){
      //     stream.end(data);
      // }


      // else if(absolutePath.slice(-3)=="png"){
      //     stream.end(data);
      // }

      else if(absolutePath.slice(-3)=="jpg"){   //FPにはjpgが必要
          stream.end(data);
      }

      else{
         //  if(absolutePath.slice(-3)=="css")
	        // console.log("返した"+absolutePath);
	        stream.end(data);
	        // console.log("返さない");
	    } 
	 });
  }
});


server.on('error', (err) => console.error(err));
server.on('socketError', (err) => console.error(err));



server.listen(3000, (err) => {
  console.log('Server running at https://localhost:3000');
  if (err) {
    console.error(err);
    return
  }
});