var html = document.documentElement;
var url = document.URL;
var domain = document.domain;
var referrer = document.referrer;
var images = document.getElementsByTagName("img");
var radios = document.getElementsByName("color");
function changecolor(newcolor){
  var elem = document.getElementById("para1");
  elem.style.color = newcolor;
}

var shopping = document.getElementById("purchases");

var paras = document.getElementsByTagName("p");
alert(paras.length);
//for(var i = 0; i< paras.length; i++){
  //alert(paras[i].getAttribute("title"));
//}

