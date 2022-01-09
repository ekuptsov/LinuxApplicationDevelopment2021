project('rhasher', 'c')
compiler = meson.get_compiler('c')
incdir = include_directories('/usr/local/include/')
libs = []
libs += compiler.find_library('rhash', dirs: ['/usr/local/lib/'],
    has_headers: ['rhash.h',], header_include_directories: ['/usr/local/include'])

extra_args = []
if get_option('with_readline')
    libs += compiler.find_library('readline', dirs: ['/usr/local/lib/'])
    libs += compiler.find_library('tinfo', dirs: ['/usr/local/lib/'])
    extra_args += ['-DWITH_READLINE']
endif

exe = executable(
    'rhasher',
    'rhasher.c',
    dependencies: libs,
    include_directories: incdir,
    c_args : extra_args,
)

test_md5 = find_program('./tests/test_md5_hex.sh')
test_sha1 = find_program('./tests/test_sha1_base64.sh')
test('compare with md5sum', test_md5)
test('compare with sha1sum', test_sha1)
