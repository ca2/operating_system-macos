//
//  UploadAudioViewController.m
//  windowing_ios
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2024-02-09 11:41
//

// in UploadAudioViewController.m file

#import "UploadAudioViewController.h"
//#import < AudioToolbox/AudioToolbox.h>

//@interface UploadAudioViewController ()
//
//@end

@implementation UploadAudioViewController

-(id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{

    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;

}

-(void)viewDidLoad
{

    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    self.title = @"Upload Audio";
    self.musicPlayer = [MPMusicPlayerController iPodMusicPlayer];
    self.audioData=nil;

}

#pragma mark Browse Audio from Device

-(void)PickAudioForIndex_iPhone
{

    if ([[[UIDevice currentDevice] model] isEqualToString:@"iPhone Simulator"]) {
        //device is simulator
        UIAlertView *alert1;
        alert1 = [[UIAlertView alloc] initWithTitle:@"Alert" message:@"There is no Audio file in the Device" delegate:self cancelButtonTitle:nil otherButtonTitles:@"Ok",nil];
        alert1.tag=2;
        [alert1 show];
        //[alert1 release],alert1=nil;
    }else{

        MPMediaPickerController *mediaPicker = [[MPMediaPickerController alloc] initWithMediaTypes:MPMediaTypeMusic];
        mediaPicker.delegate = self;
        mediaPicker.allowsPickingMultipleItems = NO; // this is the default
        [self presentViewController:mediaPicker animated:YES completion:nil];

    }

}

#pragma mark Media picker delegate methods

-(void)mediaPicker:(MPMediaPickerController *)mediaPicker didPickMediaItems:(MPMediaItemCollection *)mediaItemCollection {

    // We need to dismiss the picker
    [self dismissViewControllerAnimated:YES completion:nil];

    // Assign the selected item(s) to the music player and start playback.
    if ([mediaItemCollection count] < 1) {
        return;
    }
    song = [[mediaItemCollection items] objectAtIndex:0];
    [self handleExportTapped];

}

-(void)mediaPickerDidCancel:(MPMediaPickerController *)mediaPicker {

    // User did not select anything
    // We need to dismiss the picker

    [self dismissViewControllerAnimated:YES completion:nil ];
}

-(void)handleExportTapped{

    // get the special URL
    if (! song) {
        return;
    }

    //[self startLoaderWithLabel:@"Preparing for upload..."];

    NSURL *assetURL = [song valueForProperty:MPMediaItemPropertyAssetURL];
    AVURLAsset *songAsset = [AVURLAsset URLAssetWithURL:assetURL options:nil];

    NSLog (@"Core Audio %@ directly open library URL %@",
           coreAudioCanOpenURL (assetURL) ? @"can" : @"cannot",
           assetURL);

    NSLog (@"compatible presets for songAsset: %@",
           [AVAssetExportSession exportPresetsCompatibleWithAsset:songAsset]);


    /* approach 1: export just the song itself
     */
    AVAssetExportSession *exporter = [[AVAssetExportSession alloc]
                                      initWithAsset: songAsset
                                      presetName: AVAssetExportPresetAppleM4A];
    NSLog (@"created exporter. supportedFileTypes: %@", exporter.supportedFileTypes);
    exporter.outputFileType = @"com.apple.m4a-audio";
    NSString *exportFile = [myDocumentsDirectory() stringByAppendingPathComponent: @"exported.m4a"];
    // end of approach 1

    // set up export (hang on to exportURL so convert to PCM can find it)
    myDeleteFile(exportFile);
    //[exportURL release];
    exportURL = [NSURL fileURLWithPath:exportFile];
    exporter.outputURL = exportURL;

    // do the export
    [exporter exportAsynchronouslyWithCompletionHandler:^{
        int exportStatus = exporter.status;
        switch (exportStatus) {
            case AVAssetExportSessionStatusFailed: {
                // log error to text view
                NSError *exportError = exporter.error;
                NSLog (@"AVAssetExportSessionStatusFailed: %@", exportError);
                //errorView.text = exportError ? [exportError description] : @"Unknown failure";
                //errorView.hidden = NO;
                //[self stopLoader];
                //[self showAlertWithMessage:@"There ia an error!"];
                break;
            }
            case AVAssetExportSessionStatusCompleted: {
                NSLog (@"AVAssetExportSessionStatusCompleted");
                //fileNameLabel.text = [exporter.outputURL lastPathComponent];
                // set up AVPlayer
                //[self setUpAVPlayerForURL: exporter.outputURL];
                ///////////////// get audio data from url

                //[self stopLoader];
                //[self showAlertWithMessage:@"There ia an error!"];

                NSURL *audioUrl = exportURL;
                NSLog(@"Audio Url=%@",audioUrl);
                self.audioData = [NSData dataWithContentsOfURL:audioUrl];

                break;
            }
            case AVAssetExportSessionStatusUnknown: {
                NSLog (@"AVAssetExportSessionStatusUnknown");
                //[self stopLoader];
                //[self showAlertWithMessage:@"There ia an error!"];
                break;
            }
            case AVAssetExportSessionStatusExporting: {
                NSLog (@"AVAssetExportSessionStatusExporting");
                //[self stopLoader];
                //[self showAlertWithMessage:@"There ia an error!"];
                break;
            }
            case AVAssetExportSessionStatusCancelled: {
                NSLog (@"AVAssetExportSessionStatusCancelled");
                //[self stopLoader];
                //[self showAlertWithMessage:@"There ia an error!"];
                break;
            }
            case AVAssetExportSessionStatusWaiting: {
                NSLog (@"AVAssetExportSessionStatusWaiting");
                //[self stopLoader];
                //[self showAlertWithMessage:@"There ia an error!"];
                break;
            }
            default: {
                NSLog (@"didn't get export status");
                //[self stopLoader];
                //[self showAlertWithMessage:@"There ia an error!"];
                break;
            }
        }
    }];



}


#pragma mark conveniences

NSString* myDocumentsDirectory(){

    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    return [paths objectAtIndex:0];;

}

void myDeleteFile (NSString* path){

    if ([[NSFileManager defaultManager] fileExistsAtPath:path]) {
        NSError *deleteErr = nil;
        [[NSFileManager defaultManager] removeItemAtPath:path error:&deleteErr];
        if (deleteErr) {
            NSLog (@"Can't delete %@: %@", path, deleteErr);
        }
    }

}

// generic error handler from upcoming "Core Audio" book (thanks, Kevin!)
// if result is nonzero, prints error message and exits program.

static void CheckResult(OSStatus result, const char *operation)
{

    if (result == noErr) return;

    char errorString[20];
    // see if it appears to be a 4-char-code
    *(UInt32 *)(errorString + 1) = CFSwapInt32HostToBig(result);
    if (isprint(errorString[1]) && isprint(errorString[2]) && isprint(errorString[3]) && isprint(errorString[4])) {
        errorString[0] = errorString[5] = '\'';
        errorString[6] = '\0';
    } else
        // no, format it as an integer
        sprintf(errorString, "%d", (int)result);

    fprintf(stderr, "Error: %s (%s)\n", operation, errorString);

    exit(1);

}

#pragma mark core audio test

BOOL coreAudioCanOpenURL (NSURL* url){

    OSStatus openErr = noErr;
    AudioFileID audioFile = NULL;
    openErr = AudioFileOpenURL((__bridge CFURLRef) url,
                               kAudioFileReadPermission ,
                               0,
                               &audioFile);
    if (audioFile) {
        AudioFileClose (audioFile);
    }
    return openErr ? NO : YES;

}

@end



