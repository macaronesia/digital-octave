{
  'targets': [
    {
      'target_name': 'simple-pitch',
      'cflags!': ['-fno-exceptions'],
      'cflags_cc!': ['-fno-exceptions'],
      'sources': [
        'src/addon.cc',
        'src/pitch.cc'
      ],
      'include_dirs': [
        '<!@(node -p "require(\'node-addon-api\').include")',
        '<(module_root_dir)/vendor/portaudio/include'
      ],
      'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
      'conditions': [
        ['OS=="win"', {
          'conditions' : [
            ['target_arch=="ia32"', {
              'libraries': ['<(module_root_dir)/vendor/portaudio/lib/i386-win/portaudio_x86.lib'],
              'copies': [
                {
                  'destination': '<(module_root_dir)/build/Release/',
                  'files': ['<(module_root_dir)/vendor/portaudio/lib/i386-win/portaudio_x86.dll']
                }
              ]
            }],
            ['target_arch=="x64"', {
              'libraries': ['<(module_root_dir)/vendor/portaudio/lib/x86_64-win/portaudio_x64.lib'],
              'copies': [
                {
                  'destination': '<(module_root_dir)/build/Release/',
                  'files': ['<(module_root_dir)/vendor/portaudio/lib/x86_64-win/portaudio_x64.dll']
                }
              ]
            }]
          ]
        }],
        ['OS=="mac"', {
          'libraries': [
            '<(module_root_dir)/vendor/portaudio/lib/x86_64-mac/libportaudio.2.dylib',
            '-rpath \'@loader_path\''
          ],
          'copies': [
            {
              'destination': '<(module_root_dir)/build/Release/',
              'files': ['<(module_root_dir)/vendor/portaudio/lib/x86_64-mac/libportaudio.2.dylib']
            }
          ]
        }],
        ['OS=="linux"', {
          'conditions' : [
            ['target_arch=="ia32"', {
              'libraries': [
                '<(module_root_dir)/vendor/portaudio/lib/i386-linux-gnu/libportaudio.so.2',
                '-Wl,--disable-new-dtags -Wl,-rpath=\'$${ORIGIN}\''
              ],
              'copies': [
                {
                  'destination': '<(module_root_dir)/build/Release/',
                  'files': [
                    '<(module_root_dir)/vendor/portaudio/lib/i386-linux-gnu/libportaudio.so.2',
                    '<(module_root_dir)/vendor/portaudio/lib/i386-linux-gnu/libportaudio.so.2.0.0'
                  ]
                }
              ]
            }],
            ['target_arch=="x64"', {
              'libraries': [
                '<(module_root_dir)/vendor/portaudio/lib/x86_64-linux-gnu/libportaudio.so.2',
                '-Wl,--disable-new-dtags -Wl,-rpath=\'$${ORIGIN}\''
              ],
              'copies': [
                {
                  'destination': '<(module_root_dir)/build/Release/',
                  'files': [
                    '<(module_root_dir)/vendor/portaudio/lib/x86_64-linux-gnu/libportaudio.so.2',
                    '<(module_root_dir)/vendor/portaudio/lib/x86_64-linux-gnu/libportaudio.so.2.0.0'
                  ]
                }
              ]
            }]
          ]
        }]
      ]
    }
  ]
}
