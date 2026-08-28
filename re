<!DOCTYPE html>
<html lang="hi">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1,maximum-scale=1">
<title>Photo Editor  Pro</title>

<style>
*{box-sizing:border-box}
body{
 margin:0;background:#09070f;color:#fff;
 font-family:Arial,sans-serif
}
button,.upload{
 border:0;background:#29163d;color:#fff;
 padding:12px 15px;border-radius:13px;
 font-size:15px;cursor:pointer;white-space:nowrap
}
button:active,.upload:active{transform:scale(.96)}
.upload input{display:none}
header{
 background:linear-gradient(135deg,#6415b5,#e12c9c);
 padding:24px 15px;text-align:center
}
header h1{margin:0;font-size:27px}
.app{max-width:1100px;margin:auto;padding:15px}
.nav{
 display:flex;gap:8px;overflow-x:auto;padding:5px 0 15px
}
.search{
 width:100%;padding:15px;border:0;outline:0;
 border-radius:15px;background:#1d1627;color:#fff;
 font-size:16px;margin-bottom:12px
}
.categories{
 display:flex;gap:8px;overflow-x:auto;padding-bottom:14px
}
.templates{
 display:grid;grid-template-columns:repeat(2,1fr);gap:12px
}
.template{
 height:185px;border-radius:18px;padding:14px;
 display:flex;flex-direction:column;justify-content:flex-end;
 box-shadow:0 5px 18px #0008;cursor:pointer
}
.template b{font-size:20px;text-shadow:0 2px 8px #000}
.template small{margin-top:5px;text-shadow:0 2px 8px #000}
.hidden{display:none!important}
.editor{
 display:grid;grid-template-columns:1fr 300px;gap:14px
}
.canvasBox{
 min-height:430px;background:#17111f;border-radius:18px;
 display:flex;align-items:center;justify-content:center;
 padding:10px;position:relative
}
canvas{
 max-width:100%;max-height:68vh;background:#111;
 border-radius:10px;touch-action:none
}
.empty{position:absolute;color:#aaa;pointer-events:none}
.panel{background:#17111f;padding:16px;border-radius:18px}
.panel h3{margin:8px 0 13px}
.panel label{display:block;margin:15px 0}
input[type=range]{width:100%}
.grid{display:grid;grid-template-columns:1fr 1fr;gap:8px}
.homeCard,.exportBox{
 background:#17111f;padding:20px;border-radius:18px;
 margin-bottom:15px
}
.exportBox{text-align:center}
#exportCanvas{max-width:100%;max-height:65vh;border-radius:12px}

.modal{
 position:fixed;inset:0;background:#000e;z-index:100;
 display:flex;align-items:center;justify-content:center;padding:15px
}
.cropPanel{
 width:min(95vw,500px);background:#18121f;
 border-radius:20px;padding:15px
}
.cropArea{
 position:relative;width:100%;max-height:60vh;
 overflow:hidden;background:#000;
 display:flex;align-items:center;justify-content:center
}
#cropImage{max-width:100%;max-height:60vh;display:block}
.cropBox{
 position:absolute;border:3px solid #fff;
 box-shadow:0 0 0 9999px #0008;
 touch-action:none
}
.cropHandle{
 position:absolute;width:24px;height:24px;
 background:#fff;border-radius:50%;right:-12px;bottom:-12px
}
.modalButtons{
 display:flex;gap:8px;margin-top:12px;overflow:auto
}
@media(max-width:700px){
 .editor{grid-template-columns:1fr}
 .canvasBox{min-height:350px}
}
</style>
</head>

<body>

<header>
<h1>✨ Photo Editor Pro</h1>
</header>

<div class="app">

<!-- NAVIGATION -->
<div class="nav">

<button onclick="showPage('home')">🏠 Home</button>

<button onclick="showPage('templates')">🎨 Templates</button>

<label class="upload">
📷 Photo
<input id="photoInput" type="file" accept="image/*">
</label>

<button onclick="openCamera()">📸 Camera</button>

<button onclick="showPage('editor')">🖼️ Editor</button>

<button onclick="showExport()">📤 Export</button>

</div>


<!-- HOME -->
<section id="homePage">

<h2>📁 Your Projects</h2>

<div class="homeCard">

<h2>✨ Create New Design</h2>

<p style="color:#aaa">
Photo चुनें और अपना design बनाना शुरू करें।
</p>

<label class="upload">
📷 Select Photo
<input type="file" accept="image/*" onchange="loadPhoto(this)">
</label>

<button onclick="showPage('templates')">
🎨 Templates
</button>

</div>

<div class="grid">

<button onclick="chooseCat('Birthday')">🎂 Birthday</button>
<button onclick="chooseCat('Wedding')">💍 Wedding</button>
<button onclick="chooseCat('Festival')">🎉 Festival</button>
<button onclick="chooseCat('Business')">💼 Business</button>
<button onclick="chooseCat('Sale')">🔥 Sale</button>
<button onclick="chooseCat('Social')">📱 Social</button>
<button onclick="chooseCat('Quote')">💬 Quote</button>

</div>

</section>


<!-- TEMPLATES -->
<section id="templatesPage" class="hidden">

<h2>🎨 Photo Templates</h2>

<input id="search"
 class="search"
 placeholder="🔎 Template search करें..."
 oninput="renderTemplates()">

<div class="categories">

<button onclick="setCategory('All')">🌈 All</button>
<button onclick="setCategory('Birthday')">🎂 Birthday</button>
<button onclick="setCategory('Wedding')">💍 Wedding</button>
<button onclick="setCategory('Festival')">🎉 Festival</button>
<button onclick="setCategory('Business')">💼 Business</button>
<button onclick="setCategory('Sale')">🔥 Sale</button>
<button onclick="setCategory('Social')">📱 Social</button>
<button onclick="setCategory('Quote')">💬 Quote</button>

</div>

<div id="templateList" class="templates"></div>

</section>


<!-- EDITOR -->
<section id="editorPage" class="hidden">

<div class="nav">

<button onclick="addText()">📝 Text</button>
<button onclick="addSticker()">😀 Sticker</button>
<button onclick="openCrop()">✂️ Crop</button>
<button onclick="rotateImage()">🔄 Rotate</button>
<button onclick="zoomIn()">🔍+</button>
<button onclick="zoomOut()">🔍−</button>
<button onclick="resetEditor()">↻ Reset</button>
<button onclick="showExport()">📤 Export</button>

</div>

<div class="editor">

<div class="canvasBox">

<canvas id="canvas"></canvas>

<div id="empty" class="empty">
📷 पहले Photo चुनें
</div>

</div>

<div class="panel">

<h3>📐 Format</h3>

<div class="grid">
<button onclick="resizeCanvas(1080,1080)">1:1</button>
<button onclick="resizeCanvas(1080,1350)">4:5</button>
<button onclick="resizeCanvas(1080,1920)">9:16</button>
</div>

<h3>☀️ Adjust</h3>

<label>
Brightness
<input id="brightness" type="range"
min="0" max="200" value="100"
oninput="draw()">
</label>

<label>
Contrast
<input id="contrast" type="range"
min="0" max="200" value="100"
oninput="draw()">
</label>

<label>
Saturation
<input id="saturation" type="range"
min="0" max="200" value="100"
oninput="draw()">
</label>

<h3>✨ Filters</h3>

<div class="grid">
<button onclick="setFilter('none')">Original</button>
<button onclick="setFilter('grayscale(1)')">B&W</button>
<button onclick="setFilter('sepia(1)')">Sepia</button>
<button onclick="setFilter('contrast(1.4)')">Contrast</button>
<button onclick="setFilter('saturate(1.8)')">Vivid</button>
<button onclick="setFilter('brightness(1.25)')">Bright</button>
</div>

<h3>🛠 Tools</h3>

<div class="grid">
<button onclick="addText()">📝 Text</button>
<button onclick="addSticker()">😀 Sticker</button>
<button onclick="openCrop()">✂️ Crop</button>
<button onclick="rotateImage()">🔄 Rotate</button>
</div>

</div>
</div>

</section>


<!-- EXPORT -->
<section id="exportPage" class="hidden">

<h2>📤 Export Your Design</h2>

<div class="exportBox">

<canvas id="exportCanvas"></canvas>

<br><br>

<div class="grid">

<button onclick="saveImage()">⬇️ Download PNG</button>
<button onclick="shareImage()">📤 Share</button>

</div>

<br>

<button onclick="showPage('editor')">
← Back to Editor
</button>

</div>

</section>

</div>


<!-- CROP -->
<div id="cropModal" class="modal hidden">

<div class="cropPanel">

<h2>✂️ Crop Photo</h2>

<div class="cropArea" id="cropArea">

<img id="cropImage">

<div id="cropBox" class="cropBox">
<div class="cropHandle"></div>
</div>

</div>

<div class="modalButtons">

<button onclick="cropRatio(1)">1:1</button>
<button onclick="cropRatio(4/5)">4:5</button>
<button onclick="cropRatio(9/16)">9:16</button>
<button onclick="applyCrop()">✓ Apply</button>
<button onclick="closeCrop()">Cancel</button>

</div>

</div>
</div>


<script>

/* =========================
TEMPLATES
========================= */

const templates=[

["Birthday","🎂 Birthday","HAPPY BIRTHDAY",
"linear-gradient(135deg,#ff416c,#ff4b2b)"],

["Birthday","🎈 Party","LET'S CELEBRATE",
"linear-gradient(135deg,#f953c6,#b91d73)"],

["Birthday","🎁 Celebration","BEST WISHES",
"linear-gradient(135deg,#f7971e,#ffd200)"],

["Birthday","🥳 Kids Party","BIRTHDAY PARTY",
"linear-gradient(135deg,#00c6ff,#0072ff)"],

["Birthday","🎉 Friends","HAPPY DAY",
"linear-gradient(135deg,#7f00ff,#e100ff)"],

["Wedding","💍 Wedding","OUR WEDDING",
"linear-gradient(135deg,#8e2de2,#4a00e0)"],

["Wedding","💐 Couple","TOGETHER FOREVER",
"linear-gradient(135deg,#ff758c,#ff7eb3)"],

["Wedding","❤️ Love","FOREVER",
"linear-gradient(135deg,#cb2d3e,#ef473a)"],

["Wedding","💎 Elegant","WEDDING DAY",
"linear-gradient(135deg,#434343,#000)"],

["Wedding","🌹 Romance","TRUE LOVE",
"linear-gradient(135deg,#f00000,#dc281e)"],

["Festival","🎉 Festival","HAPPY FESTIVAL",
"linear-gradient(135deg,#11998e,#38ef7d)"],

["Festival","🪔 Diwali","HAPPY DIWALI",
"linear-gradient(135deg,#ff8008,#ffc837)"],

["Festival","🌙 Eid","EID MUBARAK",
"linear-gradient(135deg,#141e30,#243b55)"],

["Festival","🎨 Holi","HAPPY HOLI",
"linear-gradient(135deg,#ff512f,#dd2476)"],

["Festival","🎄 Christmas","MERRY CHRISTMAS",
"linear-gradient(135deg,#0f9b0f,#000)"],

["Business","💼 Business","GROW YOUR BUSINESS",
"linear-gradient(135deg,#396afc,#2948ff)"],

["Business","🚀 Startup","BUILD YOUR FUTURE",
"linear-gradient(135deg,#00c6ff,#0072ff)"],

["Business","📈 Marketing","GROW FASTER",
"linear-gradient(135deg,#0575e6,#021b79)"],

["Business","👔 Professional","PROFESSIONAL",
"linear-gradient(135deg,#232526,#414345)"],

["Business","🏆 Success","SUCCESS STARTS HERE",
"linear-gradient(135deg,#f7971e,#ffd200)"],

["Sale","🔥 Sale","BIG SALE",
"linear-gradient(135deg,#fc4a1a,#f7b733)"],

["Sale","🏷️ Discount","50% OFF",
"linear-gradient(135deg,#e52d27,#b31217)"],

["Sale","🛍️ Shopping","SPECIAL OFFER",
"linear-gradient(135deg,#f00000,#dc281e)"],

["Sale","⚡ Flash Sale","LIMITED OFFER",
"linear-gradient(135deg,#f12711,#f5af19)"],

["Sale","💥 Mega Sale","MEGA DISCOUNT",
"linear-gradient(135deg,#ff512f,#dd2476)"],

["Social","📱 Instagram","NEW POST",
"linear-gradient(135deg,#833ab4,#fd1d1d,#fcb045)"],

["Social","📸 Story","MY STORY",
"linear-gradient(135deg,#ee0979,#ff6a00)"],

["Social","👍 Social","FOLLOW ME",
"linear-gradient(135deg,#00c6ff,#0072ff)"],

["Social","✨ Modern","NEW UPDATE",
"linear-gradient(135deg,#7f00ff,#e100ff)"],

["Social","🔥 Trending","TRENDING NOW",
"linear-gradient(135deg,#f12711,#f5af19)"],

["Quote","💬 Quote","BELIEVE IN YOURSELF",
"linear-gradient(135deg,#141e30,#243b55)"],

["Quote","🌟 Motivation","NEVER GIVE UP",
"linear-gradient(135deg,#4568dc,#b06ab3)"],

["Quote","❤️ Love Quote","LOVE FOREVER",
"linear-gradient(135deg,#ff512f,#dd2476)"],

["Quote","🧠 Success","DREAM BIG",
"linear-gradient(135deg,#000428,#004e92)"],

["Quote","✨ Inspiration","BE YOURSELF",
"linear-gradient(135deg,#8360c3,#2ebf91)"]

];


let category="All";
let selectedTemplate=null;
let image=new Image();
let loaded=false;
let currentFilter="none";
let rotation=0;
let zoom=1;
let layers=[];
let draggingLayer=null;

const canvas=document.getElementById("canvas");
const ctx=canvas.getContext("2d");

const brightness=document.getElementById("brightness");
const contrast=document.getElementById("contrast");
const saturation=document.getElementById("saturation");


/* =========================
PAGE
========================= */

function showPage(page){

 ["home","templates","editor","export"]
 .forEach(x=>{
   document.getElementById(x+"Page")
   .classList.add("hidden");
 });

 document.getElementById(page+"Page")
 .classList.remove("hidden");

 if(page==="templates")
 renderTemplates();

 if(loaded) draw();
}

function chooseCat(cat){
 category=cat;
 showPage("templates");
}

function setCategory(cat){
 category=cat;
 renderTemplates();
}


/* =========================
TEMPLATES
========================= */

function renderTemplates(){

 const box=document.getElementById("templateList");

 const search=
 document.getElementById("search")
 .value.toLowerCase();

 box.innerHTML="";

 templates.forEach((t,i)=>{

   if(category!=="All" && t[0]!==category)
   return;

   if(search &&
   !(t[0]+" "+t[1]+" "+t[2])
   .toLowerCase()
   .includes(search))
   return;

   const card=document.createElement("div");

   card.className="template";
   card.style.background=t[3];

   card.innerHTML=
   "<b>"+t[1]+"</b>"+
   "<small>"+t[2]+"</small>";

   card.onclick=()=>selectTemplate(i);

   box.appendChild(card);

 });
}


/* =========================
PHOTO
========================= */

document.getElementById("photoInput")
.addEventListener("change",function(){
 if(this.files[0]) loadPhoto(this);
});

function loadPhoto(input){

 const file=input.files[0];

 if(!file)return;

 const reader=new FileReader();

 reader.onload=function(e){

   image.onload=function(){

     loaded=true;

     document.getElementById("empty")
     .style.display="none";

     rotation=0;
     zoom=1;

     showPage("editor");
     draw();
   };

   image.src=e.target.result;
 };

 reader.readAsDataURL(file);
}


/* Camera */
function openCamera(){

 const input=document.getElementById("photoInput");

 input.setAttribute("capture","environment");

 input.click();
}


/* =========================
TEMPLATE
========================= */

function selectTemplate(index){

 selectedTemplate=templates[index];

 if(
 selectedTemplate[0]==="Social" &&
 selectedTemplate[1].includes("Story")
 ){
   resizeCanvas(1080,1920);
 }else{
   resizeCanvas(1080,1080);
 }

 showPage("editor");
 draw();
}


/* =========================
CANVAS
========================= */

function resizeCanvas(w,h){

 canvas.width=w;
 canvas.height=h;

 if(loaded)draw();
}


/* =========================
DRAW
========================= */

function draw(){

 if(!loaded)return;

 ctx.clearRect(0,0,canvas.width,canvas.height);

 const scale=Math.max(
 canvas.width/image.width,
 canvas.height/image.height
 )*zoom;

 const w=image.width*scale;
 const h=image.height*scale;

 ctx.save();

 ctx.translate(
 canvas.width/2,
 canvas.height/2
 );

 ctx.rotate(
 rotation*Math.PI/180
 );

 ctx.filter=
 "brightness("+brightness.value+"%) "+
 "contrast("+contrast.value+"%) "+
 "saturate("+saturation.value+"%) "+
 currentFilter;

 ctx.drawImage(
 image,-w/2,-h/2,w,h
 );

 ctx.restore();

 ctx.filter="none";


 /* Template overlay */

 if(selectedTemplate){

   ctx.fillStyle="rgba(0,0,0,.18)";

   ctx.fillRect(
   0,0,canvas.width,canvas.height
   );

   const g=ctx.createLinearGradient(
   0,canvas.height*.55,
   0,canvas.height
   );

   g.addColorStop(0,"rgba(0,0,0,0)");
   g.addColorStop(1,"rgba(0,0,0,.85)");

   ctx.fillStyle=g;

   ctx.fillRect(
   0,0,canvas.width,canvas.height
   );

   ctx.save();

   ctx.textAlign="center";
   ctx.textBaseline="middle";

   ctx.font=
   "bold "+
   Math.max(42,canvas.width/14)+
   "px Arial";

   ctx.fillStyle="white";
   ctx.shadowColor="black";
   ctx.shadowBlur=12;

   ctx.fillText(
   selectedTemplate[2],
   canvas.width/2,
   canvas.height*.84
   );

   ctx.restore();
 }


 /* Text / stickers */

 layers.forEach(layer=>{

   ctx.save();

   ctx.textAlign="center";
   ctx.textBaseline="middle";

   ctx.font=
   "bold "+layer.size+"px Arial";

   ctx.fillStyle=layer.color||"white";

   ctx.shadowColor="black";
   ctx.shadowBlur=8;

   ctx.fillText(
   layer.text,
   layer.x,
   layer.y
   );

   ctx.restore();

 });

}


/* =========================
FILTER
========================= */

function setFilter(filter){
 currentFilter=filter;
 draw();
}


/* =========================
ROTATE / ZOOM
========================= */

function rotateImage(){

 if(!loaded){
   alert("पहले Photo चुनें");
   return;
 }

 rotation+=90;

 if(rotation>=360)
 rotation=0;

 draw();
}

function zoomIn(){
 zoom=Math.min(3,zoom+.15);
 draw();
}

function zoomOut(){
 zoom=Math.max(.5,zoom-.15);
 draw();
}


/* =========================
TEXT
========================= */

function addText(){

 if(!loaded){
   alert("पहले Photo चुनें");
   return;
 }

 const text=prompt("अपना Text लिखें:");

 if(!text)return;

 layers.push({
   text:text,
   x:canvas.width/2,
   y:canvas.height/2,
   size:55,
   color:"white"
 });

 draw();
}


/* =========================
STICKER
========================= */

function addSticker(){

 if(!loaded){
   alert("पहले Photo चुनें");
   return;
 }

 const sticker=prompt(
 "Sticker लिखें: ❤️ ⭐ 🔥 ✨ 🎉 😎 👍 🌹 🎂"
 );

 if(!sticker)return;

 layers.push({
   text:sticker,
   x:canvas.width/2,
   y:canvas.height/2,
   size:90,
   color:"white"
 });

 draw();
}


/* =========================
DRAG
========================= */

function canvasPoint(e){

 const r=canvas.getBoundingClientRect();

 return {
   x:(e.clientX-r.left)*canvas.width/r.width,
   y:(e.clientY-r.top)*canvas.height/r.height
 };
}

canvas.addEventListener("pointerdown",function(e){

 const p=canvasPoint(e);

 for(let i=layers.length-1;i>=0;i--){

   const l=layers[i];

   if(
   Math.abs(p.x-l.x)<l.size*2 &&
   Math.abs(p.y-l.y)<l.size
   ){

     draggingLayer=l;

     canvas.setPointerCapture(e.pointerId);

     break;
   }
 }
});

canvas.addEventListener("pointermove",function(e){

 if(!draggingLayer)return;

 const p=canvasPoint(e);

 draggingLayer.x=p.x;
 draggingLayer.y=p.y;

 draw();
});

canvas.addEventListener("pointerup",function(){
 draggingLayer=null;
});

canvas.addEventListener("pointercancel",function(){
 draggingLayer=null;
});


/* =========================
CROP
========================= */

const cropModal=document.getElementById("cropModal");
const cropImage=document.getElementById("cropImage");
const cropBox=document.getElementById("cropBox");
const cropArea=document.getElementById("cropArea");

function openCrop(){

 if(!loaded){
   alert("पहले Photo चुनें");
   return;
 }

 cropImage.src=image.src;

 cropImage.onload=function(){

   cropModal.classList.remove("hidden");

   setTimeout(()=>cropRatio(1),50);
 };
}

function closeCrop(){
 cropModal.classList.add("hidden");
}

function cropRatio(r){

 let area=cropArea.getBoundingClientRect();

 let width=area.width*.75;
 let height=width/r;

 if(height>area.height*.75){
   height=area.height*.75;
   width=height*r;
 }

 cropBox.style.width=width+"px";
 cropBox.style.height=height+"px";
 cropBox.style.left=(area.width-width)/2+"px";
 cropBox.style.top=(area.height-height)/2+"px";
}

let cropDragging=false;
let startX,startY,startLeft,startTop;

cropBox.addEventListener("pointerdown",function(e){

 cropDragging=true;

 startX=e.clientX;
 startY=e.clientY;

 startLeft=parseFloat(cropBox.style.left);
 startTop=parseFloat(cropBox.style.top);

 cropBox.setPointerCapture(e.pointerId);
});

cropBox.addEventListener("pointermove",function(e){

 if(!cropDragging)return;

 const area=cropArea.getBoundingClientRect();

 let left=startLeft+e.clientX-startX;
 let top=startTop+e.clientY-startY;

 const w=cropBox.offsetWidth;
 const h=cropBox.offsetHeight;

 left=Math.max(0,Math.min(left,area.width-w));
 top=Math.max(0,Math.min(top,area.height-h));

 cropBox.style.left=left+"px";
 cropBox.style.top=top+"px";
});

cropBox.addEventListener("pointerup",function(){
 cropDragging=false;
});


function applyCrop(){

 const iw=cropImage.naturalWidth;
 const ih=cropImage.naturalHeight;

 const imgRect=cropImage.getBoundingClientRect();
 const box=cropBox.getBoundingClientRect();

 let sx=(box.left-imgRect.left)*iw/imgRect.width;
 let sy=(box.top-imgRect.top)*ih/imgRect.height;

 let sw=box.width*iw/imgRect.width;
 let sh=box.height*ih/imgRect.height;

 sx=Math.max(0,sx);
 sy=Math.max(0,sy);

 sw=Math.min(sw,iw-sx);
 sh=Math.min(sh,ih-sy);

 const temp=document.createElement("canvas");

 temp.width=Math.round(sw);
 temp.height=Math.round(sh);

 const tctx=temp.getContext("2d");

 tctx.drawImage(
 image,
 sx,sy,sw,sh,
 0,0,temp.width,temp.height
 );

 const newImage=new Image();

 newImage.onload=function(){

   image=newImage;

   rotation=0;
   zoom=1;

   closeCrop();
   draw();
 };

 newImage.src=temp.toDataURL(
 "image/jpeg",.95
 );
}


/* =========================
RESET
========================= */

function resetEditor(){

 brightness.value=100;
 contrast.value=100;
 saturation.value=100;

 currentFilter="none";
 rotation=0;
 zoom=1;

 selectedTemplate=null;
 layers=[];

 draw();
}


/* =========================
EXPORT
========================= */

function showExport(){

 if(!loaded){
   alert("पहले Photo चुनें");
   return;
 }

 const out=document.getElementById("exportCanvas");

 out.width=canvas.width;
 out.height=canvas.height;

 out.getContext("2d")
 .drawImage(canvas,0,0);

 showPage("export");
}

function saveImage(){

 if(!loaded){
   alert("पहले Photo चुनें");
   return;
 }

 const link=document.createElement("a");

 link.download="photo-studio-design.png";

 link.href=canvas.toDataURL("image/png");

 link.click();
}


async function shareImage(){

 if(!loaded)return;

 canvas.toBlob(async function(blob){

   const file=new File(
   [blob],
   "photo-studio.png",
   {type:"image/png"}
   );

   try{

     if(
     navigator.share &&
     navigator.canShare &&
     navigator.canShare({files:[file]})
     ){

       await navigator.share({
         title:"Photo Studio Design",
         files:[file]
       });

     }else{

       saveImage();

     }

   }catch(e){
     saveImage();
   }

 },"image/png");
}


/* =========================
START
========================= */

renderTemplates();
showPage("home");

</script>

</body>
</html>