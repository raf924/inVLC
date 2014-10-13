#include "vlcinstance.h"

VlcInstance *VlcInstance::_vlc = NULL;

VlcInstance::VlcInstance()
{
    char * args[] = {};
    _instance = libvlc_new(0,args);
    _mediaEvents <<libvlc_MediaMetaChanged
              <<libvlc_MediaSubItemAdded
              <<libvlc_MediaDurationChanged
              <<libvlc_MediaParsedChanged
              <<libvlc_MediaFreed
              <<libvlc_MediaStateChanged
              <<libvlc_MediaSubItemTreeAdded;
    _mediaPlayerEvents<<libvlc_MediaPlayerMediaChanged
              <<libvlc_MediaPlayerNothingSpecial
              <<libvlc_MediaPlayerOpening
              <<libvlc_MediaPlayerBuffering
              <<libvlc_MediaPlayerPlaying
              <<libvlc_MediaPlayerPaused
              <<libvlc_MediaPlayerStopped
              <<libvlc_MediaPlayerForward
              <<libvlc_MediaPlayerBackward
              <<libvlc_MediaPlayerEndReached
              <<libvlc_MediaPlayerEncounteredError
              <<libvlc_MediaPlayerTimeChanged
              <<libvlc_MediaPlayerPositionChanged
              <<libvlc_MediaPlayerSeekableChanged
              <<libvlc_MediaPlayerPausableChanged
              <<libvlc_MediaPlayerTitleChanged
              <<libvlc_MediaPlayerSnapshotTaken
              <<libvlc_MediaPlayerLengthChanged
              <<libvlc_MediaPlayerVout;
    _mediaListEvents<<libvlc_MediaListItemAdded
              <<libvlc_MediaListWillAddItem
              <<libvlc_MediaListItemDeleted
              <<libvlc_MediaListWillDeleteItem
              <<libvlc_MediaListViewItemAdded
              <<libvlc_MediaListViewWillAddItem
              <<libvlc_MediaListViewItemDeleted
              <<libvlc_MediaListViewWillDeleteItem;
    _mediaListPlayerEvents<<libvlc_MediaListPlayerPlayed
              <<libvlc_MediaListPlayerNextItemSet
              <<libvlc_MediaListPlayerStopped;
}

void VlcInstance::release()
{
    libvlc_release(_instance);
}

VlcInstance * VlcInstance::load()
{
    if(!VlcInstance::_vlc){
        _vlc = new VlcInstance();
    }
    return VlcInstance::_vlc;
}


libvlc_instance_t *VlcInstance::instance()
{
    return _instance;

}
