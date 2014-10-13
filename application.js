interface.restoreChanged.connect(function (restore) {
	$(document).trigger("invlc.window.restoreChanged",restore);
	console.log("restore changed");
});
interface.lengthChanged.connect(function (length) {
	$(document).trigger("invlc.player.lengthChanged",length);
});
interface.timeChanged.connect(function (time) {
	$(document).trigger("invlc.player.timeChanged",time);
});
interface.metaDataChanged.connect(function () {
	$(document).trigger("invlc.media.metaDataChanged");
});
interface.paused.connect(function (isPaused) {
	console.log(isPaused);
	$(document).trigger("invlc.player.pause",isPaused);
});
interface.songListUpdated.connect(function (songList) {
	var sl = new Array(songList.length);
	sl = {"songList":songList};
	$(document).trigger("invlc.view.songListUpdated",sl);
});

var invlc = {};

invlc.tags = ["Title","Duration","Artist","Album","Genre", "Rating","Date"];

invlc.songList = function () {
	return interface.getSongList();
};

invlc.nowPlaying = function () {
	return interface.metaData();
};

invlc.PLAYING = 0;
invlc.PAUSED = 1;
invlc.STOPPED = 2;

invlc.play = interface.play;

invlc.action = function (action, data) {
	interface.action({action: action, data: data});
};

invlc.timeToString = function (value) {
	var d = new Date(value);
	var str = d.getHours()-1>0?(d.getHours()-1<10?"0":"")+d.getHours()-1+":":"";
	str += (d.getMinutes()<10?"0":"")+d.getMinutes()+":";
	str += (d.getSeconds()<10?"0":"")+d.getSeconds();
	return str;
};
