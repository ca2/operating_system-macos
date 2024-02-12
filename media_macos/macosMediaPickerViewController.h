//
//  macosAudioPickerViewController.h
//  windowing_macos
//
//  Created as iosAudioPickerViewController by Camilo Sasuke Thomas Borregaard
//  Sørensen on 2024-02-09 23:43
//  Refactore as maosAudioPickerViewController by Camilo Sasuke Thomas Borregaard
//  Sørensen on 2024-02-11 18:45
//

#import <Foundation/Foundation.h>
//
//// Have to add this framework
//
////CoreMedia.framework
////AudioToolbox.framework
////CoreAudio.framework
////MediaPlayer.framework
////AVFoundation.framework
//
//
////in UploadAudioViewController.h file
//
//#import <UIKit/UIKit.h>
//#import <CoreAudio/CoreAudioTypes.h>
//#import <AudioToolbox/AudioToolbox.h>
#import <MediaPlayer/MediaPlayer.h>
////#import <AVFoundation/AVFoundation.h>
//#import <CoreMedia/CoreMedia.h>
//
//

class macos_media_picker;
@class macos_nswindow;


@interface macosMediaPickerViewController : NSViewController // <MPMediaPickerControllerDelegate>
{

   //MPMediaItem *song;
   NSURL *exportURL;
   macos_media_picker * m_pmacosmediapicker;
   
}

-(id)initWithMediaPicker:(macos_media_picker *) piosmediapicker;
//@property (nonatomic, retain) NSData *audioData;
//@synthesize musicPlayer,audioData;
//@synthesize audioData;

//@property (nonatomic, strong)iosMediaPickerViewController * mediapickerHold;

-(void) pickMedia : (const char *) pszType window :(macos_nswindow *) pmacoswindow;

@end



