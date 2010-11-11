from distutils.core import *

package_name = 'SZaru'
package_version = '0.1.0'
package_description = 'a straightforward implementation of DBM'
package_author = 'Yuji Kaneda'
# package_author_email = 'info@fallabs.com'
# package_url = 'http://fallabs.com/kyotocabinet/'

module_name = 'szaru'

include_dirs = ['/usr/local/include']
extra_compile_args = []
sources = ['py_szaru.cc']
library_dirs = ['/usr/local/lib']
libraries = ['szaru', 'stdc++', 'm']

module = Extension(module_name,
                   include_dirs = include_dirs,
                   extra_compile_args = extra_compile_args,
                   sources = sources,
                   library_dirs = library_dirs,
                   libraries = libraries)
setup (name = package_name,
       version = package_version,
       description = package_description,
       # author = package_author,
       # author_email = package_author_email,
       # url = package_url,
       ext_modules = [module],
       )
