
project('fogfs', 'cpp', license: 'GPLv3+')

srcs0 = run_command('perl', '-E', 'say(join("\n", glob("src/*.cc")))')
srcs  = srcs0.stdout().strip().split('\n')

deps = [
  dependency('libsodium', version: '>= 1.0.12'),
  dependency('fuse'),
  find_library('m'),
  find_library('bsd'),
  find_library('xdg-basedir'),
]

executable('fogfs', srcs,
           include_directories: include_directories('include'),
           dependencies: deps,
           cpp_args: ['-std=gnu++11', '-g', '-Werror'])


