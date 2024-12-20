with section("parse"):
  additional_commands = {
    'ytdl_set_properties': {
      'pargs': 1,
      'flags': [],
      'kwargs': {},
    },
    'ytdl_add_library': {
      'pargs': 1,
      'flags': [],
      'kwargs': {'LINK': '*'},
    }
  }
with section("format"):
  tab_size = 4
  dangle_parens = True
