$(function(){
	$(document).on("invlc.window.restoreChanged", changeIcon);
	$(document).on("invlc.player.lengthChanged",changeLength);
	$(document).on("invlc.player.timeChanged",changeTime);
	$(document).on("invlc.media.metaDataChanged", changeMetaData);
	$(document).on("invlc.view.songListUpdated",updateView);
	$(document).on("invlc.player.pause",updatePause);
	$("#songList").on('click',function(e) {
		$(".metadata").parent().removeClass("active");
		$(e.target).parent().addClass("active")
	}).on("dblclick",function (e) {
		invlc.play($(e.target).parent().attr("id"));
	});
	$("#seeker").slider({
		id:"seeker-slider",
		tooltip:"hide",
		handle:"square",
		value:0,
		formater : function (value) {
			$("#elapsed").html(invlc.timeToString(value));
			return invlc.timeToString(value);
		}
	});
	$(".window-action").each(function (index, item) {
		$(item).click(function () {
			invlc.action($(this).data("action"));
		});
	});
	$(".player-action").each(function (index, item) {
		$(item).click(function () {
			invlc.action($(this).data("action"));
		});
	});
	$("#seeker").on("slideStart",function () {
		interface.timeChanged.disconnect(changeTime);
	});
	$("#seeker").on("slideStop",function () {
		invlc.action("seek",$("#slider").slider("getValue"));
		interface.timeChanged.connect(changeTime);
	});
	$.each(invlc.tags, function (index, item) {
		$("<th></th>").attr("id",item).html(item).appendTo("#tags");
	});
	invlc.songList();
});

function changeLength (event, length) {
	$("#seeker").slider('setAttribute',"max",length);
	$("#total").html(invlc.timeToString(length));
	changeMetaData(invlc.nowPlaying);
}

function changeTime (event, time) {
	$("#seeker").slider("setValue",time,false);
	$("#elapsed").html(invlc.timeToString(time));
}

function changeIcon (event, restore) {
	console.log("Changing icon");
	$(".window-action#restore").css("display",!restore?"":"none");
	$(".window-action#expand").css("display",!restore?"none":"");
}

function changeMetaData (event) {
	var metaData = invlc.nowPlaying();
	$(".info").each(function (index,item) {
		var key = $(this).attr("id");
		$(this).html(metaData[key]);	
	});
}

function updateView (event, songList) {
	$(".song-item").remove();
	$.each(songList["songList"],function (index, song) {
		$("<tr></tr>").attr("path",song.Path).attr("id",song.Id).addClass("song-item").appendTo("#songList");
		$.each(invlc.tags, function (index, item) {
			$("<td></td>").addClass("metadata").html(song[item]).appendTo("#"+song["Id"]);
		});
	});
}

function updatePause (event, isPaused) {
	if(isPaused!=invlc.PLAYING){
		$(".player-action > .glyphicon-pause").removeClass("glyphicon-pause").addClass("glyphicon-play");
	}
	else{
		$(".player-action > .glyphicon-play").removeClass("glyphicon-play").addClass("glyphicon-pause");		
	}
}