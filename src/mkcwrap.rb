Dir.glob("**/*").each do |file|
  base = File.basename(file)
  match = base.match(/^wrap_(.*)\.cpp/)
  if match
    typename = match[1]
    mod = file.gsub(/.*modules\/([^\/]+)\/.*/, '\1')

    raise unless mod
    type = if mod.downcase == typename.downcase
             typename
           else
             "#{mod.capitalize}_#{typename}"
           end

    c_wrap_h = File.dirname(file) + "/c_" + typename + ".h"
    if !File.exists?(c_wrap_h)
      guard = c_wrap_h.delete_prefix("modules/").gsub(/[.\/]/, "_").upcase
      guard = "LOVE_#{guard}"
      puts "#{c_wrap_h}\t#{mod}\t#{type}"

      File.open(c_wrap_h, "w") do |file|
        file << <<-CPP
#ifndef #{guard}
#define #{guard}

#include "common/config.h"
#include "common/c_wrap.h"
#include "modules/love_c/types.h"

LOVE_C_EXTERN_C_BEGIN

LOVE_C_DEFINE_OPAQUE_TYPE(#{type});

LOVE_C_EXTERN_C_END

#endif // #{guard}
CPP
      end
    end

    c_wrap_cpp = File.dirname(file) + "/c_" + typename + ".cpp"
    if !File.exists?(c_wrap_cpp)
      File.open(c_wrap_cpp, "w") do |file|
        file << <<-CPP
#include "c_#{typename}.h"

#include "common/c_wrap.h"
#include "common/Module.h"
#include "common/runtime.h"

#include "modules/love_c/runtime_c.h"

#include "#{typename}.h"

using namespace love;
using namespace love::#{mod};


CPP
      end
    end
  end
end
