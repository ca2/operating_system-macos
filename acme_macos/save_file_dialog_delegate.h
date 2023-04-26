//
//  file_dialog_template.h
//  acme_macos
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 24/04/23.
//
#pragma once


@interface save_file_dialog_delegate : NSObject<NSOpenSavePanelDelegate>
{
@public


   ::file::file_dialog * m_pdialog;

   
}

@end



