project(
	'sem3lab1',
	'cpp',
	version: '0.1',
	license: 'MIT',
	meson_version: '>=1.3',
	default_options: [
		'cpp_std=c++23',
		'warning_level=3',
		'werror=true',
	],
)

add_project_arguments(
	[
		'-D_POSIX_C_SOURCE=200809L',
		#'-DWLR_USE_UNSTABLE',
	],
	language: 'cpp',
)

cc = meson.get_compiler('cpp')

add_project_arguments(
	cc.get_supported_arguments(
		[
			'-Wundef',
			'-Wlogical-op',
			'-Wmissing-include-dirs',
			'-Wold-style-definition',
			'-Wpointer-arith',
			'-Winit-self',
			'-Wfloat-equal',
			'-Wstrict-prototypes',
			'-Wredundant-decls',
			'-Wimplicit-fallthrough',
			'-Wendif-labels',
			#'-Wstrict-aliasing=2',
			'-Woverflow',
			'-Wmissing-prototypes',
			'-Walloca',
			'-Wvla',
			'-Wformat=2',
			'-Wold-style-cast',
			'-Wshadow',

			#'-fanalyzer',
			#'-fno-math-errno',
			#'-fno-signed-zeros',
			#'-fno-trapping-math',
		],
	),
	language: 'cpp',
)

#datadir = get_option('datadir')
#sysconfdir = get_option('sysconfdir')
#prefix = get_option('prefix')

#math = cc.find_library('m', required: false)

include = include_directories('include')

src = files(
	'src/main.cpp',
)

tests = files(
	'tests/array_list_test.cpp',
	'tests/linked_list_test.cpp',
	'tests/insertion_sort_test.cpp',
	'tests/merge_sort_test.cpp',
)

src += tests

#subdir('src')

# Dependencies (from gtest.wrap)
gtest = dependency('gtest')
executable(
	'sem3lab1',
	src,
	include_directories: [include],
	dependencies: [gtest],
	#link_with: [libs],
	#install: true
)
