function insertParagraph(text){
  var str = "<p>";
  str += text;
  str += "</p>";
  document.write(str);
}

//window.onload = function(){
  //testdiv.innerHTML = "<p>This is <em>this</em> content.</p>"
//}

window.onload = function(){
  var para = document.createElement("p");
  var testdiv = document.getElementById("testdiv");
  var txt1 = document.createTextNode("This is ");
  para.appendChild(txt1);
  var emphasis = document.createElement("em");
  var txt2 = document.createTextNode("my");
  emphasis.appendChild(txt2);
  para.appendChild(emphasis);
  var txt3 = document.createTextNode(" content.");
  para.appendChild(txt3);
  testdiv.appendChild(para);
  //var text = document.createTextNode("Hello World!");
  //para.appendChild(text);

}

