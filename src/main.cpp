/*
AUTHOR       : Angel Ortiz (angelo12 AT vt DOT edu)
PROJECT      : Hybrid Rendering Engine 
LICENSE      : This code is licensed under the MIT license (MIT) (http://opensource.org/licenses/MIT)
DATE	     : 2018-09-05
PURPOSE      : Program Initialization and shutdown.
*/

#include "engine.h"
#include <stdio.h>
#include <cstdlib>

//Hybrid Rendering Engine
int main( int argc, char* args[] ){
    std::string initialSceneID = "Sponza";
    unsigned int maxFrames = 0;
    if(argc > 1){
        initialSceneID = args[1];
    }
    if(argc > 2){
        maxFrames = static_cast<unsigned int>(std::strtoul(args[2], nullptr, 10));
    }

    Engine HRE;
    if(HRE.startUp(initialSceneID)){
        HRE.run(maxFrames);
    }
    else{
        printf("HRE could not initialize successfully. Shutting down.\n");
    }
    HRE.shutDown();

    return 0;
}
