#! /usr/bin/env ruby
Gem::Specification.new do |s|
  s.platform = Gem::Platform::RUBY
  s.name = "szaru"
  s.version = "0.1.0"
  s.summary = "Portings of excellent Sawzall aggregators"
  s.author = "Yuji Kaneda"
  s.email = "llamerada@gmail.com"
  s.homepage = "http://llamerada.github.com/SZaru/"
  s.has_rdoc = true
  s.rdoc_options = ["ext"]
  s.require_paths = ["lib"]
  s.files = Dir["ext/**/*", "test/**/*", "sample/**/*", "overview.rd", "szaru-doc.rb"]
  s.test_files = Dir["test/*_spec.rb"]
  s.extensions = Dir["ext/extconf.rb"]
  s.description = <<END_DESC
Portings of excellent Sawzall aggregators.
END_DESC
end
