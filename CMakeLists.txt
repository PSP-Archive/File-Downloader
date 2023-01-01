cmake_minimum_required(VERSION 3.5)

project(
    File_Downloader
    VERSION 1.0
    DESCRIPTION "File Downloader"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES 
    main.cpp 
    setupwifi.cpp 
    keyboard.cpp 
    setup.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (PSP)

    message(STATUS "PSP found")

    set(BUILD_PRX 1)

    set(DEFAULT_STUBS
        pspdebug 
        pspdisplay 
        pspge 
        pspctrl 
        pspnet 
        pspnet_apctl
    )

    set(LIBS
        SDLmain 
        SDL_image 
        SDL_ttf 
        SDL 
        png 
        jpeg 
        m 
        z 
        freetype 
        stdc++ 
        curl 
        pspsdk 
        pspctrl  
        psprtc 
        psppower 
        pspgu 
        pspaudiolib 
        pspaudio 
        psphprm 
        bz2 
        GL 
        pspvfpu 
        pspirkeyb
    )

    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS} ${DEFAULT_STUBS})        

    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ICON0.png
        BACKGROUND_PATH ${CMAKE_CURRENT_SOURCE_DIR}/PIC1.png
        PREVIEW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ICON0.png
    )

else()

    message(STATUS "PSP not found")

endif()