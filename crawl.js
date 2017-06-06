w=window.open("");
list=document.getElementsByTagName('tr');
for (i=5;i<list.length;i++){
	w.document.writeln(i+"<br>");
	node=list[i];
	title=node.children[2].children[0].children[0].children[0].innerText;
	w.document.writeln(title+"<br>");
}