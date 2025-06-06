/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2014 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/* Ported from original test\common.c file. */

#include "SDL_config.h"
#include "SDL_test.h"

#include <stdio.h>

#define VIDEO_USAGE \
"[--video driver] [--renderer driver] [--gldebug] [--info all|video|modes|render|event] [--log all|error|system|audio|video|render|input] [--display N] [--fullscreen | --fullscreen-desktop | --windows N] [--title title] [--icon icon.bmp] [--center | --position X,Y] [--geometry WxH] [--min-geometry WxH] [--max-geometry WxH] [--logical WxH] [--scale N] [--depth N] [--refresh R] [--vsync] [--noframe] [--resize] [--minimize] [--maximize] [--grab] [--allow-highdpi]"

#define AUDIO_USAGE \
"[--rate N] [--format U8|S8|U16|U16LE|U16BE|S16|S16LE|S16BE] [--channels N] [--samples N]"

SDLTest_CommonState *
SDLTest_CommonCreateState(char **argv, Uint32 flags)
{
    SDLTest_CommonState *state = (SDLTest_CommonState *)SDL_calloc(1, sizeof(*state));
    if (!state) {
        SDL_OutOfMemory();
        return NULL;
    }

    /* Initialize some defaults */
    state->argv = argv;
    state->flags = flags;
    state->window_title = argv[0];
    state->window_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
    state->window_x = SDL_WINDOWPOS_UNDEFINED;
    state->window_y = SDL_WINDOWPOS_UNDEFINED;
    state->window_w = DEFAULT_WINDOW_WIDTH;
    state->window_h = DEFAULT_WINDOW_HEIGHT;
    state->num_windows = 1;
    state->audiospec.freq = 22050;
    state->audiospec.format = AUDIO_S16;
    state->audiospec.channels = 2;
    state->audiospec.samples = 2048;

    /* Set some very sane GL defaults */
    state->gl_red_size = 3;
    state->gl_green_size = 3;
    state->gl_blue_size = 2;
    state->gl_alpha_size = 0;
    state->gl_buffer_size = 0;
    state->gl_depth_size = 16;
    state->gl_stencil_size = 0;
    state->gl_double_buffer = 1;
    state->gl_accum_red_size = 0;
    state->gl_accum_green_size = 0;
    state->gl_accum_blue_size = 0;
    state->gl_accum_alpha_size = 0;
    state->gl_stereo = 0;
    state->gl_multisamplebuffers = 0;
    state->gl_multisamplesamples = 0;
    state->gl_retained_backing = 1;
    state->gl_accelerated = -1;
    state->gl_debug = 0;

    return state;
}

int
SDLTest_CommonArg(SDLTest_CommonState * state, int index)
{
    char **argv = state->argv;

    if (SDL_strcasecmp(argv[index], "--video") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->videodriver = argv[index];
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--renderer") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->renderdriver = argv[index];
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--gldebug") == 0) {
        state->gl_debug = 1;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--info") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        if (SDL_strcasecmp(argv[index], "all") == 0) {
            state->verbose |=
                (VERBOSE_VIDEO | VERBOSE_MODES | VERBOSE_RENDER |
                 VERBOSE_EVENT);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "video") == 0) {
            state->verbose |= VERBOSE_VIDEO;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "modes") == 0) {
            state->verbose |= VERBOSE_MODES;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "render") == 0) {
            state->verbose |= VERBOSE_RENDER;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "event") == 0) {
            state->verbose |= VERBOSE_EVENT;
            return 2;
        }
        return -1;
    }
    if (SDL_strcasecmp(argv[index], "--log") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        if (SDL_strcasecmp(argv[index], "all") == 0) {
            SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "error") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "system") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_SYSTEM, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "audio") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_AUDIO, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "video") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_VIDEO, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "render") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_RENDER, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "input") == 0) {
            SDL_LogSetPriority(SDL_LOG_CATEGORY_INPUT, SDL_LOG_PRIORITY_VERBOSE);
            return 2;
        }
        return -1;
    }
    if (SDL_strcasecmp(argv[index], "--display") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->display = SDL_atoi(argv[index]);
        if (SDL_WINDOWPOS_ISUNDEFINED(state->window_x)) {
            state->window_x = SDL_WINDOWPOS_UNDEFINED_DISPLAY(state->display);
            state->window_y = SDL_WINDOWPOS_UNDEFINED_DISPLAY(state->display);
        }
        if (SDL_WINDOWPOS_ISCENTERED(state->window_x)) {
            state->window_x = SDL_WINDOWPOS_CENTERED_DISPLAY(state->display);
            state->window_y = SDL_WINDOWPOS_CENTERED_DISPLAY(state->display);
        }
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--fullscreen") == 0) {
        state->window_flags |= SDL_WINDOW_FULLSCREEN;
        state->num_windows = 1;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--fullscreen-desktop") == 0) {
        state->window_flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        state->num_windows = 1;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--allow-highdpi") == 0) {
        state->window_flags |= SDL_WINDOW_ALLOW_HIGHDPI;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--windows") == 0) {
        ++index;
        if (!argv[index] || !SDL_isdigit(*argv[index])) {
            return -1;
        }
        if (!(state->window_flags & SDL_WINDOW_FULLSCREEN)) {
            state->num_windows = SDL_atoi(argv[index]);
        }
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--title") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->window_title = argv[index];
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--icon") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->window_icon = argv[index];
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--center") == 0) {
        state->window_x = SDL_WINDOWPOS_CENTERED;
        state->window_y = SDL_WINDOWPOS_CENTERED;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--position") == 0) {
        char *x, *y;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        x = argv[index];
        y = argv[index];
        while (*y && *y != ',') {
            ++y;
        }
        if (!*y) {
            return -1;
        }
        *y++ = '\0';
        state->window_x = SDL_atoi(x);
        state->window_y = SDL_atoi(y);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--geometry") == 0) {
        char *w, *h;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        w = argv[index];
        h = argv[index];
        while (*h && *h != 'x') {
            ++h;
        }
        if (!*h) {
            return -1;
        }
        *h++ = '\0';
        state->window_w = SDL_atoi(w);
        state->window_h = SDL_atoi(h);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--min-geometry") == 0) {
        char *w, *h;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        w = argv[index];
        h = argv[index];
        while (*h && *h != 'x') {
            ++h;
        }
        if (!*h) {
            return -1;
        }
        *h++ = '\0';
        state->window_minW = SDL_atoi(w);
        state->window_minH = SDL_atoi(h);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--max-geometry") == 0) {
        char *w, *h;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        w = argv[index];
        h = argv[index];
        while (*h && *h != 'x') {
            ++h;
        }
        if (!*h) {
            return -1;
        }
        *h++ = '\0';
        state->window_maxW = SDL_atoi(w);
        state->window_maxH = SDL_atoi(h);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--logical") == 0) {
        char *w, *h;
        ++index;
        if (!argv[index]) {
            return -1;
        }
        w = argv[index];
        h = argv[index];
        while (*h && *h != 'x') {
            ++h;
        }
        if (!*h) {
            return -1;
        }
        *h++ = '\0';
        state->logical_w = SDL_atoi(w);
        state->logical_h = SDL_atoi(h);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--scale") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->scale = (float)SDL_atof(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--depth") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->depth = SDL_atoi(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--refresh") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->refresh_rate = SDL_atoi(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--vsync") == 0) {
        state->render_flags |= SDL_RENDERER_PRESENTVSYNC;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--noframe") == 0) {
        state->window_flags |= SDL_WINDOW_BORDERLESS;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--resize") == 0) {
        state->window_flags |= SDL_WINDOW_RESIZABLE;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--minimize") == 0) {
        state->window_flags |= SDL_WINDOW_MINIMIZED;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--maximize") == 0) {
        state->window_flags |= SDL_WINDOW_MAXIMIZED;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--grab") == 0) {
        state->window_flags |= SDL_WINDOW_INPUT_GRABBED;
        return 1;
    }
    if (SDL_strcasecmp(argv[index], "--rate") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->audiospec.freq = SDL_atoi(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--format") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        if (SDL_strcasecmp(argv[index], "U8") == 0) {
            state->audiospec.format = AUDIO_U8;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "S8") == 0) {
            state->audiospec.format = AUDIO_S8;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "U16") == 0) {
            state->audiospec.format = AUDIO_U16;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "U16LE") == 0) {
            state->audiospec.format = AUDIO_U16LSB;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "U16BE") == 0) {
            state->audiospec.format = AUDIO_U16MSB;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "S16") == 0) {
            state->audiospec.format = AUDIO_S16;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "S16LE") == 0) {
            state->audiospec.format = AUDIO_S16LSB;
            return 2;
        }
        if (SDL_strcasecmp(argv[index], "S16BE") == 0) {
            state->audiospec.format = AUDIO_S16MSB;
            return 2;
        }
        return -1;
    }
    if (SDL_strcasecmp(argv[index], "--channels") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->audiospec.channels = (Uint8) SDL_atoi(argv[index]);
        return 2;
    }
    if (SDL_strcasecmp(argv[index], "--samples") == 0) {
        ++index;
        if (!argv[index]) {
            return -1;
        }
        state->audiospec.samples = (Uint16) SDL_atoi(argv[index]);
        return 2;
    }
    if ((SDL_strcasecmp(argv[index], "-h") == 0)
        || (SDL_strcasecmp(argv[index], "--help") == 0)) {
        /* Print the usage message */
        return -1;
    }
    if (SDL_strcmp(argv[index], "-NSDocumentRevisionsDebugMode") == 0) {
    /* Debug flag sent by Xcode */
        return 2;
    }
    return 0;
}

const char *
SDLTest_CommonUsage(SDLTest_CommonState * state)
{
    switch (state->flags & (SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    case SDL_INIT_VIDEO:
        return VIDEO_USAGE;
    case SDL_INIT_AUDIO:
        return AUDIO_USAGE;
    case (SDL_INIT_VIDEO | SDL_INIT_AUDIO):
        return VIDEO_USAGE " " AUDIO_USAGE;
    default:
        return "";
    }
}

static void
SDLTest_PrintRendererFlag(Uint32 flag)
{
    switch (flag) {
    case SDL_RENDERER_PRESENTVSYNC:
        fprintf(stderr, "PresentVSync");
        break;
    case SDL_RENDERER_ACCELERATED:
        fprintf(stderr, "Accelerated");
        break;
    default:
        fprintf(stderr, "0x%8.8x", flag);
        break;
    }
}

static void
SDLTest_PrintPixelFormat(Uint32 format)
{
    switch (format) {
    case SDL_PIXELFORMAT_UNKNOWN:
        fprintf(stderr, "Unknwon");
        break;
    case SDL_PIXELFORMAT_INDEX1LSB:
        fprintf(stderr, "Index1LSB");
        break;
    case SDL_PIXELFORMAT_INDEX1MSB:
        fprintf(stderr, "Index1MSB");
        break;
    case SDL_PIXELFORMAT_INDEX4LSB:
        fprintf(stderr, "Index4LSB");
        break;
    case SDL_PIXELFORMAT_INDEX4MSB:
        fprintf(stderr, "Index4MSB");
        break;
    case SDL_PIXELFORMAT_INDEX8:
        fprintf(stderr, "Index8");
        break;
    case SDL_PIXELFORMAT_RGB332:
        fprintf(stderr, "RGB332");
        break;
    case SDL_PIXELFORMAT_RGB444:
        fprintf(stderr, "RGB444");
        break;
    case SDL_PIXELFORMAT_RGB555:
        fprintf(stderr, "RGB555");
        break;
    case SDL_PIXELFORMAT_BGR555:
        fprintf(stderr, "BGR555");
        break;
    case SDL_PIXELFORMAT_ARGB4444:
        fprintf(stderr, "ARGB4444");
        break;
    case SDL_PIXELFORMAT_ABGR4444:
        fprintf(stderr, "ABGR4444");
        break;
    case SDL_PIXELFORMAT_ARGB1555:
        fprintf(stderr, "ARGB1555");
        break;
    case SDL_PIXELFORMAT_ABGR1555:
        fprintf(stderr, "ABGR1555");
        break;
    case SDL_PIXELFORMAT_RGB565:
        fprintf(stderr, "RGB565");
        break;
    case SDL_PIXELFORMAT_BGR565:
        fprintf(stderr, "BGR565");
        break;
    case SDL_PIXELFORMAT_RGB24:
        fprintf(stderr, "RGB24");
        break;
    case SDL_PIXELFORMAT_BGR24:
        fprintf(stderr, "BGR24");
        break;
    case SDL_PIXELFORMAT_RGB888:
        fprintf(stderr, "RGB888");
        break;
    case SDL_PIXELFORMAT_BGR888:
        fprintf(stderr, "BGR888");
        break;
    case SDL_PIXELFORMAT_ARGB8888:
        fprintf(stderr, "ARGB8888");
        break;
    case SDL_PIXELFORMAT_RGBA8888:
        fprintf(stderr, "RGBA8888");
        break;
    case SDL_PIXELFORMAT_ABGR8888:
        fprintf(stderr, "ABGR8888");
        break;
    case SDL_PIXELFORMAT_BGRA8888:
        fprintf(stderr, "BGRA8888");
        break;
    case SDL_PIXELFORMAT_ARGB2101010:
        fprintf(stderr, "ARGB2101010");
        break;
    case SDL_PIXELFORMAT_YV12:
        fprintf(stderr, "YV12");
        break;
    case SDL_PIXELFORMAT_IYUV:
        fprintf(stderr, "IYUV");
        break;
    case SDL_PIXELFORMAT_YUY2:
        fprintf(stderr, "YUY2");
        break;
    case SDL_PIXELFORMAT_UYVY:
        fprintf(stderr, "UYVY");
        break;
    case SDL_PIXELFORMAT_YVYU:
        fprintf(stderr, "YVYU");
        break;
    default:
        fprintf(stderr, "0x%8.8x", format);
        break;
    }
}

static void
SDLTest_PrintRenderer(SDL_RendererInfo * info)
{
    int i, count;

    fprintf(stderr, "  Renderer %s:\n", info->name);

    fprintf(stderr, "    Flags: 0x%8.8X", info->flags);
    fprintf(stderr, " (");
    count = 0;
    for (i = 0; i < sizeof(info->flags) * 8; ++i) {
        Uint32 flag = (1 << i);
        if (info->flags & flag) {
            if (count > 0) {
                fprintf(stderr, " | ");
            }
            SDLTest_PrintRendererFlag(flag);
            ++count;
        }
    }
    fprintf(stderr, ")\n");

    fprintf(stderr, "    Texture formats (%d): ", info->num_texture_formats);
    for (i = 0; i < (int) info->num_texture_formats; ++i) {
        if (i > 0) {
            fprintf(stderr, ", ");
        }
        SDLTest_PrintPixelFormat(info->texture_formats[i]);
    }
    fprintf(stderr, "\n");

    if (info->max_texture_width || info->max_texture_height) {
        fprintf(stderr, "    Max Texture Size: %dx%d\n",
                info->max_texture_width, info->max_texture_height);
    }
}

static SDL_Surface *
SDLTest_LoadIcon(const char *file)
{
    SDL_Surface *icon;

    /* Load the icon surface */
    icon = SDL_LoadBMP(file);
    if (icon == NULL) {
        fprintf(stderr, "Couldn't load %s: %s\n", file, SDL_GetError());
        return (NULL);
    }

    if (icon->format->palette) {
        /* Set the colorkey */
        SDL_SetColorKey(icon, 1, *((Uint8 *) icon->pixels));
    }

    return (icon);
}

SDL_bool
SDLTest_CommonInit(SDLTest_CommonState * state)
{
    int i, j, m, n, w, h;
    SDL_DisplayMode fullscreen_mode;

    if (state->flags & SDL_INIT_VIDEO) {
        if (state->verbose & VERBOSE_VIDEO) {
            n = SDL_GetNumVideoDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in video drivers\n");
            } else {
                fprintf(stderr, "Built-in video drivers:");
                for (i = 0; i < n; ++i) {
                    if (i > 0) {
                        fprintf(stderr, ",");
                    }
                    fprintf(stderr, " %s", SDL_GetVideoDriver(i));
                }
                fprintf(stderr, "\n");
            }
        }
        if (SDL_VideoInit(state->videodriver) < 0) {
            fprintf(stderr, "Couldn't initialize video driver: %s\n",
                    SDL_GetError());
            return SDL_FALSE;
        }
        if (state->verbose & VERBOSE_VIDEO) {
            fprintf(stderr, "Video driver: %s\n",
                    SDL_GetCurrentVideoDriver());
        }

        /* Upload GL settings */
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, state->gl_red_size);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, state->gl_green_size);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, state->gl_blue_size);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, state->gl_alpha_size);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, state->gl_double_buffer);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, state->gl_buffer_size);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, state->gl_depth_size);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, state->gl_stencil_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, state->gl_accum_red_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, state->gl_accum_green_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, state->gl_accum_blue_size);
        SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, state->gl_accum_alpha_size);
        SDL_GL_SetAttribute(SDL_GL_STEREO, state->gl_stereo);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, state->gl_multisamplebuffers);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, state->gl_multisamplesamples);
        if (state->gl_accelerated >= 0) {
            SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL,
                                state->gl_accelerated);
        }
        SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, state->gl_retained_backing);
        if (state->gl_major_version) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, state->gl_major_version);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, state->gl_minor_version);
        }
        if (state->gl_debug) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        }
        if (state->gl_profile_mask) {
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, state->gl_profile_mask);
        }

#ifdef __APPLE__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

        if (state->verbose & VERBOSE_MODES) {
            SDL_Rect bounds;
            SDL_DisplayMode mode;
            int bpp;
            Uint32 Rmask, Gmask, Bmask, Amask;
#if SDL_VIDEO_DRIVER_WINDOWS
			int adapterIndex = 0;
			int outputIndex = 0;
#endif
            n = SDL_GetNumVideoDisplays();
            fprintf(stderr, "Number of displays: %d\n", n);
            for (i = 0; i < n; ++i) {
                fprintf(stderr, "Display %d: %s\n", i, SDL_GetDisplayName(i));

                SDL_zero(bounds);
                SDL_GetDisplayBounds(i, &bounds);
                fprintf(stderr, "Bounds: %dx%d at %d,%d\n", bounds.w, bounds.h, bounds.x, bounds.y);

                SDL_GetDesktopDisplayMode(i, &mode);
                SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask, &Gmask,
                                           &Bmask, &Amask);
                fprintf(stderr,
                        "  Current mode: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                        mode.w, mode.h, mode.refresh_rate, bpp,
                        SDL_GetPixelFormatName(mode.format));
                if (Rmask || Gmask || Bmask) {
                    fprintf(stderr, "      Red Mask   = 0x%.8x\n", Rmask);
                    fprintf(stderr, "      Green Mask = 0x%.8x\n", Gmask);
                    fprintf(stderr, "      Blue Mask  = 0x%.8x\n", Bmask);
                    if (Amask)
                        fprintf(stderr, "      Alpha Mask = 0x%.8x\n", Amask);
                }

                /* Print available fullscreen video modes */
                m = SDL_GetNumDisplayModes(i);
                if (m == 0) {
                    fprintf(stderr, "No available fullscreen video modes\n");
                } else {
                    fprintf(stderr, "  Fullscreen video modes:\n");
                    for (j = 0; j < m; ++j) {
                        SDL_GetDisplayMode(i, j, &mode);
                        SDL_PixelFormatEnumToMasks(mode.format, &bpp, &Rmask,
                                                   &Gmask, &Bmask, &Amask);
                        fprintf(stderr,
                                "    Mode %d: %dx%d@%dHz, %d bits-per-pixel (%s)\n",
                                j, mode.w, mode.h, mode.refresh_rate, bpp,
                                SDL_GetPixelFormatName(mode.format));
                        if (Rmask || Gmask || Bmask) {
                            fprintf(stderr, "        Red Mask   = 0x%.8x\n",
                                    Rmask);
                            fprintf(stderr, "        Green Mask = 0x%.8x\n",
                                    Gmask);
                            fprintf(stderr, "        Blue Mask  = 0x%.8x\n",
                                    Bmask);
                            if (Amask)
                                fprintf(stderr,
                                        "        Alpha Mask = 0x%.8x\n",
                                        Amask);
                        }
                    }
                }

#if SDL_VIDEO_DRIVER_WINDOWS
				/* Print the D3D9 adapter index */
				adapterIndex = SDL_Direct3D9GetAdapterIndex( i );
				fprintf( stderr, "D3D9 Adapter Index: %d", adapterIndex );

				/* Print the DXGI adapter and output indices */
				SDL_DXGIGetOutputInfo(i, &adapterIndex, &outputIndex);
				fprintf( stderr, "DXGI Adapter Index: %d  Output Index: %d", adapterIndex, outputIndex );
#endif
            }
        }

        if (state->verbose & VERBOSE_RENDER) {
            SDL_RendererInfo info;

            n = SDL_GetNumRenderDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in render drivers\n");
            } else {
                fprintf(stderr, "Built-in render drivers:\n");
                for (i = 0; i < n; ++i) {
                    SDL_GetRenderDriverInfo(i, &info);
                    SDLTest_PrintRenderer(&info);
                }
            }
        }

        SDL_zero(fullscreen_mode);
        switch (state->depth) {
        case 8:
            fullscreen_mode.format = SDL_PIXELFORMAT_INDEX8;
            break;
        case 15:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB555;
            break;
        case 16:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB565;
            break;
        case 24:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB24;
            break;
        default:
            fullscreen_mode.format = SDL_PIXELFORMAT_RGB888;
            break;
        }
        fullscreen_mode.refresh_rate = state->refresh_rate;

        state->windows =
            (SDL_Window **) SDL_malloc(state->num_windows *
                                        sizeof(*state->windows));
        state->renderers =
            (SDL_Renderer **) SDL_malloc(state->num_windows *
                                        sizeof(*state->renderers));
        state->targets =
            (SDL_Texture **) SDL_malloc(state->num_windows *
                                        sizeof(*state->targets));
        if (!state->windows || !state->renderers) {
            fprintf(stderr, "Out of memory!\n");
            return SDL_FALSE;
        }
        for (i = 0; i < state->num_windows; ++i) {
            char title[1024];

            if (state->num_windows > 1) {
                SDL_snprintf(title, SDL_arraysize(title), "%s %d",
                             state->window_title, i + 1);
            } else {
                SDL_strlcpy(title, state->window_title, SDL_arraysize(title));
            }
            state->windows[i] =
                SDL_CreateWindow(title, state->window_x, state->window_y,
                                 state->window_w, state->window_h,
                                 state->window_flags);
            if (!state->windows[i]) {
                fprintf(stderr, "Couldn't create window: %s\n",
                        SDL_GetError());
                return SDL_FALSE;
            }
            if (state->window_minW || state->window_minH) {
                SDL_SetWindowMinimumSize(state->windows[i], state->window_minW, state->window_minH);
            }
            if (state->window_maxW || state->window_maxH) {
                SDL_SetWindowMaximumSize(state->windows[i], state->window_maxW, state->window_maxH);
            }
            SDL_GetWindowSize(state->windows[i], &w, &h);
            if (!(state->window_flags & SDL_WINDOW_RESIZABLE) &&
                (w != state->window_w || h != state->window_h)) {
                printf("Window requested size %dx%d, got %dx%d\n", state->window_w, state->window_h, w, h);
                state->window_w = w;
                state->window_h = h;
            }
            if (SDL_SetWindowDisplayMode(state->windows[i], &fullscreen_mode) < 0) {
                fprintf(stderr, "Can't set up fullscreen display mode: %s\n",
                        SDL_GetError());
                return SDL_FALSE;
            }

            if (state->window_icon) {
                SDL_Surface *icon = SDLTest_LoadIcon(state->window_icon);
                if (icon) {
                    SDL_SetWindowIcon(state->windows[i], icon);
                    SDL_FreeSurface(icon);
                }
            }

            SDL_ShowWindow(state->windows[i]);

            state->renderers[i] = NULL;
            state->targets[i] = NULL;

            if (!state->skip_renderer
                && (state->renderdriver
                    || !(state->window_flags & SDL_WINDOW_OPENGL))) {
                m = -1;
                if (state->renderdriver) {
                    SDL_RendererInfo info;
                    n = SDL_GetNumRenderDrivers();
                    for (j = 0; j < n; ++j) {
                        SDL_GetRenderDriverInfo(j, &info);
                        if (SDL_strcasecmp(info.name, state->renderdriver) ==
                            0) {
                            m = j;
                            break;
                        }
                    }
                    if (m == n) {
                        fprintf(stderr,
                                "Couldn't find render driver named %s",
                                state->renderdriver);
                        return SDL_FALSE;
                    }
                }
                state->renderers[i] = SDL_CreateRenderer(state->windows[i],
                                            m, state->render_flags);
                if (!state->renderers[i]) {
                    fprintf(stderr, "Couldn't create renderer: %s\n",
                            SDL_GetError());
                    return SDL_FALSE;
                }
                if (state->logical_w && state->logical_h) {
                    SDL_RenderSetLogicalSize(state->renderers[i], state->logical_w, state->logical_h);
                } else if (state->scale) {
                    SDL_RenderSetScale(state->renderers[i], state->scale, state->scale);
                }
                if (state->verbose & VERBOSE_RENDER) {
                    SDL_RendererInfo info;

                    fprintf(stderr, "Current renderer:\n");
                    SDL_GetRendererInfo(state->renderers[i], &info);
                    SDLTest_PrintRenderer(&info);
                }
            }
        }
    }

    if (state->flags & SDL_INIT_AUDIO) {
        if (state->verbose & VERBOSE_AUDIO) {
            n = SDL_GetNumAudioDrivers();
            if (n == 0) {
                fprintf(stderr, "No built-in audio drivers\n");
            } else {
                fprintf(stderr, "Built-in audio drivers:");
                for (i = 0; i < n; ++i) {
                    if (i > 0) {
                        fprintf(stderr, ",");
                    }
                    fprintf(stderr, " %s", SDL_GetAudioDriver(i));
                }
                fprintf(stderr, "\n");
            }
        }
        if (SDL_AudioInit(state->audiodriver) < 0) {
            fprintf(stderr, "Couldn't initialize audio driver: %s\n",
                    SDL_GetError());
            return SDL_FALSE;
        }
        if (state->verbose & VERBOSE_VIDEO) {
            fprintf(stderr, "Audio driver: %s\n",
                    SDL_GetCurrentAudioDriver());
        }

        if (SDL_OpenAudio(&state->audiospec, NULL) < 0) {
            fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
            return SDL_FALSE;
        }
    }

    return SDL_TRUE;
}

static const char *
ControllerAxisName(const SDL_GameControllerAxis axis)
{
    switch (axis)
    {
#define AXIS_CASE(ax) case SDL_CONTROLLER_AXIS_##ax: return #ax
        AXIS_CASE(INVALID);
        AXIS_CASE(LEFTX);
        AXIS_CASE(LEFTY);
        AXIS_CASE(RIGHTX);
        AXIS_CASE(RIGHTY);
        AXIS_CASE(TRIGGERLEFT);
        AXIS_CASE(TRIGGERRIGHT);
#undef AXIS_CASE
default: return "???";
    }
}

static const char *
ControllerButtonName(const SDL_GameControllerButton button)
{
    switch (button)
    {
#define BUTTON_CASE(btn) case SDL_CONTROLLER_BUTTON_##btn: return #btn
        BUTTON_CASE(INVALID);
        BUTTON_CASE(A);
        BUTTON_CASE(B);
        BUTTON_CASE(X);
        BUTTON_CASE(Y);
        BUTTON_CASE(BACK);
        BUTTON_CASE(GUIDE);
        BUTTON_CASE(START);
        BUTTON_CASE(LEFTSTICK);
        BUTTON_CASE(RIGHTSTICK);
        BUTTON_CASE(LEFTSHOULDER);
        BUTTON_CASE(RIGHTSHOULDER);
        BUTTON_CASE(DPAD_UP);
        BUTTON_CASE(DPAD_DOWN);
        BUTTON_CASE(DPAD_LEFT);
        BUTTON_CASE(DPAD_RIGHT);
#undef BUTTON_CASE
default: return "???";
    }
}

static void
SDLTest_PrintEvent(SDL_Event * event)
{
    if ((event->type == SDL_MOUSEMOTION) || (event->type == SDL_FINGERMOTION)) {
        /* Mouse and finger motion are really spammy */
        return;
    }

    switch (event->type) {
    case SDL_WINDOWEVENT:
        switch (event->window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("SDL EVENT: Window %d shown", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("SDL EVENT: Window %d hidden", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_Log("SDL EVENT: Window %d exposed", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            SDL_Log("SDL EVENT: Window %d moved to %d,%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("SDL EVENT: Window %d resized to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("SDL EVENT: Window %d changed size to %dx%d",
                    event->window.windowID, event->window.data1,
                    event->window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            SDL_Log("SDL EVENT: Window %d minimized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_Log("SDL EVENT: Window %d maximized", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            SDL_Log("SDL EVENT: Window %d restored", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            SDL_Log("SDL EVENT: Mouse entered window %d",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("SDL EVENT: Mouse left window %d", event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            SDL_Log("SDL EVENT: Window %d gained keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_Log("SDL EVENT: Window %d lost keyboard focus",
                    event->window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("SDL EVENT: Window %d closed", event->window.windowID);
            break;
        default:
            SDL_Log("SDL EVENT: Window %d got unknown event %d",
                    event->window.windowID, event->window.event);
            break;
        }
        break;
    case SDL_KEYDOWN:
        SDL_Log("SDL EVENT: Keyboard: key pressed  in window %d: scancode 0x%08X = %s, keycode 0x%08X = %s",
                event->key.windowID,
                event->key.keysym.scancode,
                SDL_GetScancodeName(event->key.keysym.scancode),
                event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
        break;
    case SDL_KEYUP:
        SDL_Log("SDL EVENT: Keyboard: key released in window %d: scancode 0x%08X = %s, keycode 0x%08X = %s",
                event->key.windowID,
                event->key.keysym.scancode,
                SDL_GetScancodeName(event->key.keysym.scancode),
                event->key.keysym.sym, SDL_GetKeyName(event->key.keysym.sym));
        break;
    case SDL_TEXTINPUT:
        SDL_Log("SDL EVENT: Keyboard: text input \"%s\" in window %d",
                event->text.text, event->text.windowID);
        break;
    case SDL_MOUSEMOTION:
        SDL_Log("SDL EVENT: Mouse: moved to %d,%d (%d,%d) in window %d",
                event->motion.x, event->motion.y,
                event->motion.xrel, event->motion.yrel,
                event->motion.windowID);
        break;
    case SDL_MOUSEBUTTONDOWN:
        SDL_Log("SDL EVENT: Mouse: button %d pressed at %d,%d with click count %d in window %d",
                event->button.button, event->button.x, event->button.y, event->button.clicks,
                event->button.windowID);
        break;
    case SDL_MOUSEBUTTONUP:
        SDL_Log("SDL EVENT: Mouse: button %d released at %d,%d with click count %d in window %d",
                event->button.button, event->button.x, event->button.y, event->button.clicks,
                event->button.windowID);
        break;
    case SDL_MOUSEWHEEL:
        SDL_Log("SDL EVENT: Mouse: wheel scrolled %d in x and %d in y in window %d",
                event->wheel.x, event->wheel.y, event->wheel.windowID);
        break;
    case SDL_JOYDEVICEADDED:
        SDL_Log("SDL EVENT: Joystick index %d attached",
            event->jdevice.which);
        break;
    case SDL_JOYDEVICEREMOVED:
        SDL_Log("SDL EVENT: Joystick %d removed",
            event->jdevice.which);
        break;
    case SDL_JOYBALLMOTION:
        SDL_Log("SDL EVENT: Joystick %d: ball %d moved by %d,%d",
                event->jball.which, event->jball.ball, event->jball.xrel,
                event->jball.yrel);
        break;
    case SDL_JOYHATMOTION:
        {
            const char *position = "UNKNOWN";
            switch (event->jhat.value) {
            case SDL_HAT_CENTERED:
                position = "CENTER";
                break;
            case SDL_HAT_UP:
                position = "UP";
                break;
            case SDL_HAT_RIGHTUP:
                position = "RIGHTUP";
                break;
            case SDL_HAT_RIGHT:
                position = "RIGHT";
                break;
            case SDL_HAT_RIGHTDOWN:
                position = "RIGHTDOWN";
                break;
            case SDL_HAT_DOWN:
                position = "DOWN";
                break;
            case SDL_HAT_LEFTDOWN:
                position = "LEFTDOWN";
                break;
            case SDL_HAT_LEFT:
                position = "LEFT";
                break;
            case SDL_HAT_LEFTUP:
                position = "LEFTUP";
                break;
            }
            SDL_Log("SDL EVENT: Joystick %d: hat %d moved to %s", event->jhat.which,
                event->jhat.hat, position);
        }
        break;
    case SDL_JOYBUTTONDOWN:
        SDL_Log("SDL EVENT: Joystick %d: button %d pressed",
                event->jbutton.which, event->jbutton.button);
        break;
    case SDL_JOYBUTTONUP:
        SDL_Log("SDL EVENT: Joystick %d: button %d released",
                event->jbutton.which, event->jbutton.button);
        break;
    case SDL_CONTROLLERDEVICEADDED:
        SDL_Log("SDL EVENT: Controller index %d attached",
            event->cdevice.which);
        break;
    case SDL_CONTROLLERDEVICEREMOVED:
        SDL_Log("SDL EVENT: Controller %d removed",
            event->cdevice.which);
        break;
    case SDL_CONTROLLERAXISMOTION:
        SDL_Log("SDL EVENT: Controller %d axis %d ('%s') value: %d",
            event->caxis.which,
            event->caxis.axis,
            ControllerAxisName((SDL_GameControllerAxis)event->caxis.axis),
            event->caxis.value);
        break;
    case SDL_CONTROLLERBUTTONDOWN:
        SDL_Log("SDL EVENT: Controller %d button %d ('%s') down",
            event->cbutton.which, event->cbutton.button,
            ControllerButtonName((SDL_GameControllerButton)event->cbutton.button));
        break;
    case SDL_CONTROLLERBUTTONUP:
        SDL_Log("SDL EVENT: Controller %d button %d ('%s') up",
            event->cbutton.which, event->cbutton.button,
            ControllerButtonName((SDL_GameControllerButton)event->cbutton.button));
        break;
    case SDL_CLIPBOARDUPDATE:
        SDL_Log("SDL EVENT: Clipboard updated");
        break;

    case SDL_FINGERDOWN:
    case SDL_FINGERUP:
        SDL_Log("SDL EVENT: Finger: %s touch=%ld, finger=%ld, x=%f, y=%f, dx=%f, dy=%f, pressure=%f",
                (event->type == SDL_FINGERDOWN) ? "down" : "up",
                (long) event->tfinger.touchId,
                (long) event->tfinger.fingerId,
                event->tfinger.x, event->tfinger.y,
                event->tfinger.dx, event->tfinger.dy, event->tfinger.pressure);
        break;

    case SDL_QUIT:
        SDL_Log("SDL EVENT: Quit requested");
        break;
    case SDL_USEREVENT:
        SDL_Log("SDL EVENT: User event %d", event->user.code);
        break;
    default:
        SDL_Log("Unknown event %d", event->type);
        break;
    }
}

static void
SDLTest_ScreenShot(SDL_Renderer *renderer)
{
    SDL_Rect viewport;
    SDL_Surface *surface;

    if (!renderer) {
        return;
    }

    SDL_RenderGetViewport(renderer, &viewport);
    surface = SDL_CreateRGBSurface(0, viewport.w, viewport.h, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
                    0x00FF0000, 0x0000FF00, 0x000000FF,
#else
                    0x000000FF, 0x0000FF00, 0x00FF0000,
#endif
                    0x00000000);
    if (!surface) {
        fprintf(stderr, "Couldn't create surface: %s\n", SDL_GetError());
        return;
    }

    if (SDL_RenderReadPixels(renderer, NULL, surface->format->format,
                             surface->pixels, surface->pitch) < 0) {
        fprintf(stderr, "Couldn't read screen: %s\n", SDL_GetError());
        SDL_free(surface);
        return;
    }

    if (SDL_SaveBMP(surface, "screenshot.bmp") < 0) {
        fprintf(stderr, "Couldn't save screenshot.bmp: %s\n", SDL_GetError());
        SDL_free(surface);
        return;
    }
}

static void
FullscreenTo(int index, int windowId)
{
    Uint32 flags;
    struct SDL_Rect rect = { 0, 0, 0, 0 };
    SDL_Window *window = SDL_GetWindowFromID(windowId);
    if (!window) {
        return;
    }

    SDL_GetDisplayBounds( index, &rect );

    flags = SDL_GetWindowFlags(window);
    if (flags & SDL_WINDOW_FULLSCREEN) {
        SDL_SetWindowFullscreen( window, SDL_FALSE );
        SDL_Delay( 15 );
    }

    SDL_SetWindowPosition( window, rect.x, rect.y );
    SDL_SetWindowFullscreen( window, SDL_TRUE );
}

void
SDLTest_CommonEvent(SDLTest_CommonState * state, SDL_Event * event, int *done)
{
    int i;
    static SDL_MouseMotionEvent lastEvent;

    if (state->verbose & VERBOSE_EVENT) {
        SDLTest_PrintEvent(event);
    }

    switch (event->type) {
    case SDL_WINDOWEVENT:
        switch (event->window.event) {
        case SDL_WINDOWEVENT_CLOSE:
            {
                SDL_Window *window = SDL_GetWindowFromID(event->window.windowID);
                if (window) {
                    for (i = 0; i < state->num_windows; ++i) {
                        if (window == state->windows[i]) {
                            if (state->targets[i]) {
                                SDL_DestroyTexture(state->targets[i]);
                                state->targets[i] = NULL;
                            }
                            if (state->renderers[i]) {
                                SDL_DestroyRenderer(state->renderers[i]);
                                state->renderers[i] = NULL;
                            }
                            SDL_DestroyWindow(state->windows[i]);
                            state->windows[i] = NULL;
                            break;
                        }
                    }
                }
            }
            break;
        }
        break;
    case SDL_KEYDOWN: {
        SDL_bool withControl = !!(event->key.keysym.mod & KMOD_CTRL);
        SDL_bool withShift = !!(event->key.keysym.mod & KMOD_SHIFT);
        SDL_bool withAlt = !!(event->key.keysym.mod & KMOD_ALT);

        switch (event->key.keysym.sym) {
            /* Add hotkeys here */
        case SDLK_PRINTSCREEN: {
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    for (i = 0; i < state->num_windows; ++i) {
                        if (window == state->windows[i]) {
                            SDLTest_ScreenShot(state->renderers[i]);
                        }
                    }
                }
            }
            break;
        case SDLK_EQUALS:
            if (withControl) {
                /* Ctrl-+ double the size of the window */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    SDL_SetWindowSize(window, w*2, h*2);
                }
            }
            break;
        case SDLK_MINUS:
            if (withControl) {
                /* Ctrl-- half the size of the window */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    SDL_SetWindowSize(window, w/2, h/2);
                }
            }
            break;
        case SDLK_c:
            if (withControl) {
                /* Ctrl-C copy awesome text! */
                SDL_SetClipboardText("SDL rocks!\nYou know it!");
                printf("Copied text to clipboard\n");
            }
            if (withAlt) {
                /* Alt-C toggle a render clip rectangle */
                for (i = 0; i < state->num_windows; ++i) {
                    int w, h;
                    if (state->renderers[i]) {
                        SDL_Rect clip;
                        SDL_GetWindowSize(state->windows[i], &w, &h);
                        SDL_RenderGetClipRect(state->renderers[i], &clip);
                        if (SDL_RectEmpty(&clip)) {
                            clip.x = w/4;
                            clip.y = h/4;
                            clip.w = w/2;
                            clip.h = h/2;
                            SDL_RenderSetClipRect(state->renderers[i], &clip);
                        } else {
                            SDL_RenderSetClipRect(state->renderers[i], NULL);
                        }
                    }
                }
            }
            break;
        case SDLK_v:
            if (withControl) {
                /* Ctrl-V paste awesome text! */
                char *text = SDL_GetClipboardText();
                if (*text) {
                    printf("Clipboard: %s\n", text);
                } else {
                    printf("Clipboard is empty\n");
                }
                SDL_free(text);
            }
            break;
        case SDLK_g:
            if (withControl) {
                /* Ctrl-G toggle grab */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    SDL_SetWindowGrab(window, !SDL_GetWindowGrab(window) ? SDL_TRUE : SDL_FALSE);
                }
            }
            break;
        case SDLK_m:
            if (withControl) {
                /* Ctrl-M maximize */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if (flags & SDL_WINDOW_MAXIMIZED) {
                        SDL_RestoreWindow(window);
                    } else {
                        SDL_MaximizeWindow(window);
                    }
                }
            }
            break;
        case SDLK_r:
            if (withControl) {
                /* Ctrl-R toggle mouse relative mode */
                SDL_SetRelativeMouseMode(!SDL_GetRelativeMouseMode() ? SDL_TRUE : SDL_FALSE);
            }
            break;
        case SDLK_z:
            if (withControl) {
                /* Ctrl-Z minimize */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    SDL_MinimizeWindow(window);
                }
            }
            break;
        case SDLK_RETURN:
            if (withControl) {
                /* Ctrl-Enter toggle fullscreen */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if (flags & SDL_WINDOW_FULLSCREEN) {
                        SDL_SetWindowFullscreen(window, SDL_FALSE);
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                    }
                }
            } else if (withAlt) {
                /* Alt-Enter toggle fullscreen desktop */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if (flags & SDL_WINDOW_FULLSCREEN) {
                        SDL_SetWindowFullscreen(window, SDL_FALSE);
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                }
            } else if (withShift) {
                /* Shift-Enter toggle fullscreen desktop / fullscreen */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    Uint32 flags = SDL_GetWindowFlags(window);
                    if ((flags & SDL_WINDOW_FULLSCREEN_DESKTOP) == SDL_WINDOW_FULLSCREEN_DESKTOP) {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                    } else {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                }
            }

            break;
        case SDLK_b:
            if (withControl) {
                /* Ctrl-B toggle window border */
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                if (window) {
                    const Uint32 flags = SDL_GetWindowFlags(window);
                    const SDL_bool b = ((flags & SDL_WINDOW_BORDERLESS) != 0) ? SDL_TRUE : SDL_FALSE;
                    SDL_SetWindowBordered(window, b);
                }
            }
            break;
        case SDLK_0:
            if (withControl) {
                SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);
                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Test Message", "You're awesome!", window);
            }
            break;
        case SDLK_1:
            if (withControl) {
                FullscreenTo(0, event->key.windowID);
            }
            break;
        case SDLK_2:
            if (withControl) {
                FullscreenTo(1, event->key.windowID);
            }
            break;
        case SDLK_ESCAPE:
            *done = 1;
            break;
        case SDLK_SPACE:
        {
            char message[256];
            SDL_Window *window = SDL_GetWindowFromID(event->key.windowID);

            SDL_snprintf(message, sizeof(message), "(%i, %i), rel (%i, %i)\n", lastEvent.x, lastEvent.y, lastEvent.xrel, lastEvent.yrel);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Last mouse position", message, window);
            break;
        }
        default:
            break;
        }
        break;
    }
    case SDL_QUIT:
        *done = 1;
        break;
    case SDL_MOUSEMOTION:
        lastEvent = event->motion;
        break;
    }
}

void
SDLTest_CommonQuit(SDLTest_CommonState * state)
{
    int i;

    SDL_free(state->windows);
    if (state->targets) {
        for (i = 0; i < state->num_windows; ++i) {
            if (state->targets[i]) {
                SDL_DestroyTexture(state->targets[i]);
            }
        }
        SDL_free(state->targets);
    }
    if (state->renderers) {
        for (i = 0; i < state->num_windows; ++i) {
            if (state->renderers[i]) {
                SDL_DestroyRenderer(state->renderers[i]);
            }
        }
        SDL_free(state->renderers);
    }
    if (state->flags & SDL_INIT_VIDEO) {
        SDL_VideoQuit();
    }
    if (state->flags & SDL_INIT_AUDIO) {
        SDL_AudioQuit();
    }
    SDL_free(state);
    SDL_Quit();
}

/* vi: set ts=4 sw=4 expandtab: */
