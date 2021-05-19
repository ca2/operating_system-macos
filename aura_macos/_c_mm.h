//
//  _c_mm.h
//  aura_macos
//
//  Created by Camilo Sasuke on 2021-05-18 17:56 BRT <3ThomasBS_!!
//  Copyright © 2021 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#pragma once


void nsapp_activate_ignoring_other_apps(int i);
void nsapp_activation_policy_regular();
void nsapp_activation_policy_prohibited();
void nsapp_activation_policy_accessory();
bool nsapp_activation_policy_is_accessory();
bool nsapp_activation_policy_is_regular();
bool nsapp_activation_policy_is_prohibited();

void ns_app_close();


