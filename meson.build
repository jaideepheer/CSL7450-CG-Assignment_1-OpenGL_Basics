project(
    'GraphicsAssignment', 'cpp',
    version: '1.0.0',
    default_options: ['cpp_std=c++17']
)

# Define dependencies
cc = meson.get_compiler('cpp')
deps = []
includes = []

# Commands for static linking freeglut
add_global_arguments('-DFREEGLUT_STATIC', '-DGLEW_STATIC', language : ['cpp', 'c'])
add_global_link_arguments('-DFREEGLUT_STATIC', '-DGLEW_STATIC', language : ['cpp', 'c'])

if meson.is_cross_build()
    # set to winndows gui mode
    add_global_link_arguments('-Wl,--subsystem,windows', language : ['cpp', 'c'])
    GL = cc.find_library('opengl32')
    WINMM = cc.find_library('winmm')
    GDI32 = cc.find_library('gdi32')
    GLU = cc.find_library('glu32')
    glut = cc.find_library('freeglut_static', dirs: ['/mingw/lib/x64'])
    includes += [include_directories('/mingw/include')]
    deps += [GL, GLU, WINMM, GDI32, glut]
else
    GL = cc.find_library('GL')
    GLU = cc.find_library('GLU', static: true)
    glut = cc.find_library('glut', static: true)
    glut_deps = [cc.find_library('X11'), cc.find_library('Xi'), cc.find_library('Xxf86vm')]
    deps += glut_deps + [GL, GLU, glut]
endif

# Src dir.
subdir('src')