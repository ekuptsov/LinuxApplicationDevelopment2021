project('rhasher', 'c')
compiler = meson.get_compiler('c')
incdir = include_directories('/usr/local/include/')
librhash = compiler.find_library('rhash', dirs: ['/usr/local/lib/'],
    has_headers: ['rhash.h',], header_include_directories: ['/usr/local/include'])
# librhash = compiler.find_library('librhash', dirs: ['/usr/local/lib/'])

executable(
    'rhasher',
    'rhasher.c',
    dependencies: [librhash,],
    include_directories: incdir
)
