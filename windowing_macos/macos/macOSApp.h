//
//  RoundWindowApp.h
//  axis
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 27/09/14.
//
//

//
//  RoundWindowFrameView.h
//  RoundWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//


#include "acme_windowing_appkit/macos_app.h"
//#include "apex/platform/menu/menu.h"


//class menu_shared;
//class application_menu;
//class application_menu_callback;


@interface macOSApp : macos_app < NSMenuDelegate >
{
@public

   //NSMenu *                         m_menu;
   //NSMutableArray *     m_menuitema;
   //NSMutableArray *     m_menuida;

}

-(NSMenu *) applicationDockMenu:(NSApplication*)sender;
//- (void)play:(id)sender;
-(void)continueInitialization;
//- (void) ns_add_menu :(NSMenu *) menuParent withParent: (const char *) pszParent  withSharedMenu : (menu_shared *) pmenushared;
- (id)initWithApplicationMenu:(::application_menu *) papplicationmenu andCommandHandler: (::command_handler *) pcommandhandler;

@end
