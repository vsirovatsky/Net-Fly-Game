#include "Preferences.h"



Preferences::Preferences(void)
{
	CL_String ns_config = "config";
	CL_String ipName = "config:ip";
	CL_String portName = "config:port";
 
	CL_File file("config.ini");
 
	CL_DomDocument document(file);
	CL_DomElement root = document.get_document_element();
	CL_DomElement body = root.named_item_ns(ns_config, "login").to_element();
	CL_DomNode cur = body.get_first_child();
	while (!cur.is_null())
	{
		if (cur.get_namespace_uri() == ns_config)
		{
			CL_String name = cur.get_node_name();
			CL_DomElement element = cur.to_element();
			CL_String value = element.get_text();
			if ( name == ipName )
			{
				ip = value;
				CL_Console::write_line("ip: %1", value);
			}
			if ( name == portName )
			{
				port = value;
				CL_Console::write_line("port: %1", value);
			}
		}
		cur = cur.get_next_sibling();
	}
	file.close();
}


Preferences::~Preferences(void)
{
}
