//  
//  Created by liqing on 2015-Mar-20.  
//  
//  
  
#ifndef __GALLERY_CAMERA__  
#define __GALLERY_CAMERA__  
  
class GalleryCamera 
{  
public:  
    static void dispatchEvent(int type,const char* str);

    static void callOpenImageChoose();
    static void callOpenCamera();
    static void callScanBarcode();
};  
  
#endif
