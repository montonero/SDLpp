#! /usr/bin/env python
# the following two variables are used by the target "waf dist"
VERSION='0.0.1'

# these variables are mandatory ('/' are converted automatically)
top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_c compiler_cxx')
    
def configure(ctx):
    ctx.load('compiler_c compiler_cxx')      
    ctx.check_cfg(
            path='sdl2-config',
            args='--cflags --libs',
            package='',
            uselib_store='SDL2')


def build(ctx):
    includes_ = ['include', '.']
    ss = ctx.path.ant_glob('src/*.cpp')

    cxxflags = ['-std=c++14']
    use_ = ["SDL2", "mathfu", "vectorial"]
    linkflags_ = []
    if ctx.env.emscripten:
	emscripten_flags = [
	    'FULL_ES2=1',
	    # 'USE_ZLIB=1',
	    # 'USE_LIBPNG=1',
	    'DEMANGLE_SUPPORT=1',
	    'OUTLINING_LIMIT=20000',
	    'ASSERTIONS=1',
	    'USE_SDL=2',
	    'USE_SDL_TTF=2',
	    'USE_SDL_IMAGE=2',
	]
	emscripten_flags = reduce(lambda a, v: a + ['-s', v], emscripten_flags, [])
	emscripten_flags += [
	    '-Os'
        ]

        cxxflags += emscripten_flags
        linkflags_ += emscripten_flags
        use_ = use_ + ['SDL2_image']

    ctx.stlib(
        target='SDLpp',
        use = use_,
        # name = 's7static',
        # features='c cstlib',
        cxxflags = cxxflags,
        linkflags = linkflags_,
        source = ss,
        defines = ['_SDL2'],
        includes = includes_,
	# lib = ['SDL2', 'SDL2_ttf', 'SDL2_image'],
        export_includes = includes_
    )
