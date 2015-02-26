/** Serialization library for ccsds-tool, static part.
 * */
#ifndef _CCSDS_TOOL_SERIALIZE_HH_
#define _CCSDS_TOOL_SERIALIZE_HH_ 1

namespace ccsds_tool
{
  template<typename X> void doit(X const & x)
  {
    x.doit();
  }

  template<std::size_t N, typename X> void doit(X(&array)[N])
  {
    for (auto i = 0; i < N; i++)
    {
      doit(array[i]);
    }
  }
}

#endif

