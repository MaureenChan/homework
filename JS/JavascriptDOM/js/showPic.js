function addLoadEvent(func){
  var oldonload = window.onload;
  if(typeof window.onload != 'function'){
    window.onload = func;
  }else{
    window.onload = function(){
      oldonload();
      func();
    }
  }
}

function insertAfter(newElement, targetElement){
  var parent = targetElement.parentNode;
  if(parent.lastChild == targetElement){
    parent.appendChild(newElement);
  }else{
    parent.insertBefore(newElement, targetElement.nextSibling);
  }
}


function showPic(whichpic){
  if(!document.getElementById("placeholder"))
    return false;
  var source = whichpic.getAttribute("href");
  var placeholder = document.getElementById("placeholder");
  placeholder.setAttribute("src", source);
  if(!document.getElementById("description"))
    return false;
  if(whichpic.getAttribute("title")){
    var text = whichpic.getAttribute("title");
  }else{
    var text = "";
  }
  var description = document.getElementById("description");
  if(description.firstChild.nodeType == 3){
    description.firstChild.nodeValue = text;
  }
  return false;
}

//function countBodyChildren(){
  //var body_element = document.getElementsByTagName("body")[0];
//}

//window.onload = countBodyChildren;

function prepareGallery(){
  var gallery = document.getElementById("imagegallery");
  var links = gallery.getElementsByTagName("a");
  for (var i = 0; i < links.length; i++){
    links[i].onclick = function(){
      showPic(this);
      return false;
      }
  }
}


function preparePlaceholder(){
  var placeholder = document.createElement("img");
  placeholder.setAttribute("id", "placeholder");
  placeholder.setAttribute("src", "images/placeholder.png");
  placeholder.setAttribute("alt", "my image gallery");
  var description = document.createElement("p");
  var desctext = document.createTextNode("Choose an image");
  var gallery = document.getElementById("imagegallery");
  insertAfter(placeholder,gallery);
  insertAfter(description, placeholder);
}

addLoadEvent(preparePlaceholder);
addLoadEvent(prepareGallery);
