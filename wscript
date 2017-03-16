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
    ctx.stlib(
        target='SDLpp',
        use = ["SDL2", "mathfu", "vectorial"],
        # name = 's7static',
        # features='c cstlib',
        cxxflags     = ['-std=c++14'],
        source = ss,
        defines = ['_SDL2'],
        includes = includes_,
        export_includes = includes_
    )
