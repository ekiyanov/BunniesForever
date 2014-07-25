//
//  ObjectFactory.h
//  BunniesForever
//
//  Created by Kiyanov Eugene on 25/07/14.
//
//

#ifndef __BunniesForever__ObjectFactory__
#define __BunniesForever__ObjectFactory__

#include <iostream>

#include "StringFactory.h"
class RowObject;
typedef StringFactory<RowObject*,std::string>   RowObjectFactory;

#endif /* defined(__BunniesForever__ObjectFactory__) */
