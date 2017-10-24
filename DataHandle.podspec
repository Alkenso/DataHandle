Pod::Spec.new do |s|
  s.name            = "DataHandle"
  s.version         = "0.0.1"
  s.summary         = "DataHandle provides unified processing of completely different data sources under a single interface."
  s.author          = { "Alkenso" => "alkensox@gmail.com" }

  s.homepage        = "https://github.com/Alkenso/DataHandle"
  s.source          = { :git => "https://github.com/Alkenso/DataHandle.git", :tag => "#{s.version}" }
  s.source_files    = "DataHandle/**/*.{h,cpp}"
  s.header_dir      = "DataHandle/include"
  s.license         = { :type => "MIT", :file => "LICENSE" }

  s.ios.deployment_target = "7.0"
  s.osx.deployment_target = "10.8"

  s.libraries             = 'DataHandle'
  s.requires_arc          = false

end
