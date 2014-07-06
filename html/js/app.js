$(function(){
	interface.restoreChanged.connect(changeIcon);
	$(".window-action").each(function (index, item) {
		$(item).click(function () {
			interface.action({action:$(this).attr("id")});
		})
	});
	$("#close").click(function(event) {
		Qt.quit();
	});
	changeIcon();
});

function changeIcon (restore) {
		$(".window-action#restore").css("display",restore?"":"none");
		$(".window-action#expand").css("display",restore?"none":"");
}