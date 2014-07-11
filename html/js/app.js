$(function(){
	try{
		interface.restoreChanged.connect(changeIcon);
		interface.lengthChanged.connect(changeLength);
		interface.timeChanged.connect(changeTime);
		interface.metaDataChanged.connect(changeMetaData);
	}
	catch(e)
	{

	}
	$("#seeker").slider({
		id:"seeker-slider",
		tooltip:"hide",
		handle:"square",
		value:0,
		formater : function (value) {
			$("#elapsed").html(timeToString(value));
			return timeToString(value);
		}
	});
	$(".window-action").each(function (index, item) {
		$(item).click(function () {
			interface.action({action:$(this).attr("id")});
		});
	});
	$("#seeker").on("slideStart",function () {
		interface.timeChanged.disconnect(changeTime);
	});
	$("#seeker").on("slideStop",function () {
		interface.action({action:"seek",data:$("#slider").slider("getValue")});
		interface.timeChanged.connect(changeTime);
	});
	changeIcon();
});

function changeLength (length) {
	$("#seeker").slider('setAttribute',"max",length);
	$("#total").html(timeToString(length));
	changeMetaData(interface.nowPlaying);
}

function changeTime (time) {
	$("#seeker").slider("setValue",time,false);
	$("#elapsed").html(timeToString(time));
}

function changeIcon (restore) {
	$(".window-action#restore").css("display",restore?"":"none");
	$(".window-action#expand").css("display",restore?"none":"");
}

function changeMetaData (metaData) {
	//console.log(interface.nowPlaying);
	$(".metadata").each(function (index,item) {
		var key = $(this).attr("id");
		key = key.replace(/^[a-z]/g,key.charAt(0).toUpperCase());
		console.log(key);
		$(this).html(metaData[key]);	
	});
}

function timeToString (value) {
	var d = new Date(value);
	var str = d.getHours()-1>0?(d.getHours()-1<10?"0":"")+d.getHours()-1+":":"";
	str += (d.getMinutes()<10?"0":"")+d.getMinutes()+":";
	str += (d.getSeconds()<10?"0":"")+d.getSeconds();
	return str;
}