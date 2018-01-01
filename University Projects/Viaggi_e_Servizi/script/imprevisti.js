//Change classname for hiding and visualizing of a insert window
function fumetto(){
	element=document.getElementById('bubble');
	if(element.className=='bubble-hide'){
		element.setAttribute("class","bubble-visualize bubble-visualize-top");
	}else{
		element.setAttribute("class","bubble-hide");
	}
}