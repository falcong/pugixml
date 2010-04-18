#include "common.hpp"

TEST_XML(dom_attr_assign, "<node attr1='' attr2='' attr3='' attr4='' attr5=''/>")
{
	xml_node node = doc.child(T("node"));

	node.attribute(T("attr1")) = T("v1");
	xml_attribute() = T("v1");

	node.attribute(T("attr2")) = -2147483647 - 1;
	xml_attribute() = -2147483647 - 1;

	node.attribute(T("attr3")) = 2147483647u;
	xml_attribute() = 2147483647;

	node.attribute(T("attr4")) = 0.5;
	xml_attribute() = 0.5;

	node.attribute(T("attr5")) = true;
	xml_attribute() = true;

	CHECK_NODE(node, T("<node attr1=\"v1\" attr2=\"-2147483648\" attr3=\"2147483647\" attr4=\"0.5\" attr5=\"true\" />"));
}

TEST_XML(dom_attr_set_value, "<node attr1='' attr2='' attr3='' attr4='' attr5=''/>")
{
	xml_node node = doc.child(T("node"));

	CHECK(node.attribute(T("attr1")).set_value(T("v1")));
	CHECK(!xml_attribute().set_value(T("v1")));

	CHECK(node.attribute(T("attr2")).set_value(-2147483647 - 1));
	CHECK(!xml_attribute().set_value(-2147483647 - 1));

	CHECK(node.attribute(T("attr3")).set_value(2147483647u));
	CHECK(!xml_attribute().set_value(2147483647));

	CHECK(node.attribute(T("attr4")).set_value(0.5));
	CHECK(!xml_attribute().set_value(0.5));

	CHECK(node.attribute(T("attr5")).set_value(true));
	CHECK(!xml_attribute().set_value(true));

	CHECK_NODE(node, T("<node attr1=\"v1\" attr2=\"-2147483648\" attr3=\"2147483647\" attr4=\"0.5\" attr5=\"true\" />"));
}

TEST_XML(dom_node_set_name, "<node>text</node>")
{
	CHECK(doc.child(T("node")).set_name(T("n")));
	CHECK(!doc.child(T("node")).first_child().set_name(T("n")));
	CHECK(!xml_node().set_name(T("n")));

	CHECK_NODE(doc, T("<n>text</n>"));
}

TEST_XML(dom_node_set_value, "<node>text</node>")
{
	CHECK(doc.child(T("node")).first_child().set_value(T("no text")));
	CHECK(!doc.child(T("node")).set_value(T("no text")));
	CHECK(!xml_node().set_value(T("no text")));

	CHECK_NODE(doc, T("<node>no text</node>"));
}

TEST_XML(dom_node_set_value_allocated, "<node>text</node>")
{
	CHECK(doc.child(T("node")).first_child().set_value(T("no text")));
	CHECK(!doc.child(T("node")).set_value(T("no text")));
	CHECK(!xml_node().set_value(T("no text")));
	CHECK(doc.child(T("node")).first_child().set_value(T("no text at all")));

	CHECK_NODE(doc, T("<node>no text at all</node>"));
}

TEST_XML(dom_node_append_attribute, "<node><child/></node>")
{
	CHECK(xml_node().append_attribute(T("a")) == xml_attribute());
	CHECK(doc.append_attribute(T("a")) == xml_attribute());
	
	xml_attribute a1 = doc.child(T("node")).append_attribute(T("a1"));
	CHECK(a1);
	a1 = T("v1");

	xml_attribute a2 = doc.child(T("node")).append_attribute(T("a2"));
	CHECK(a2 && a1 != a2);
	a2 = T("v2");

	xml_attribute a3 = doc.child(T("node")).child(T("child")).append_attribute(T("a3"));
	CHECK(a3 && a1 != a3 && a2 != a3);
	a3 = T("v3");

	CHECK_NODE(doc, T("<node a1=\"v1\" a2=\"v2\"><child a3=\"v3\" /></node>"));
}

TEST_XML(dom_node_insert_attribute_after, "<node a1='v1'><child a2='v2'/></node>")
{
	CHECK(xml_node().insert_attribute_after(T("a"), xml_attribute()) == xml_attribute());

	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	xml_attribute a1 = node.attribute(T("a1"));
	xml_attribute a2 = child.attribute(T("a2"));

	CHECK(node.insert_attribute_after(T("a"), xml_attribute()) == xml_attribute());
	CHECK(node.insert_attribute_after(T("a"), a2) == xml_attribute());
	
	xml_attribute a3 = node.insert_attribute_after(T("a3"), a1);
	CHECK(a3 && a3 != a2 && a3 != a1);
	a3 = T("v3");

	xml_attribute a4 = node.insert_attribute_after(T("a4"), a1);
	CHECK(a4 && a4 != a3 && a4 != a2 && a4 != a1);
	a4 = T("v4");

	xml_attribute a5 = node.insert_attribute_after(T("a5"), a3);
	CHECK(a5 && a5 != a4 && a5 != a3 && a5 != a2 && a5 != a1);
	a5 = T("v5");

	CHECK(child.insert_attribute_after(T("a"), a4) == xml_attribute());

	CHECK_NODE(doc, T("<node a1=\"v1\" a4=\"v4\" a3=\"v3\" a5=\"v5\"><child a2=\"v2\" /></node>"));
}

TEST_XML(dom_node_insert_attribute_before, "<node a1='v1'><child a2='v2'/></node>")
{
	CHECK(xml_node().insert_attribute_before(T("a"), xml_attribute()) == xml_attribute());

	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	xml_attribute a1 = node.attribute(T("a1"));
	xml_attribute a2 = child.attribute(T("a2"));

	CHECK(node.insert_attribute_before(T("a"), xml_attribute()) == xml_attribute());
	CHECK(node.insert_attribute_before(T("a"), a2) == xml_attribute());
	
	xml_attribute a3 = node.insert_attribute_before(T("a3"), a1);
	CHECK(a3 && a3 != a2 && a3 != a1);
	a3 = T("v3");

	xml_attribute a4 = node.insert_attribute_before(T("a4"), a1);
	CHECK(a4 && a4 != a3 && a4 != a2 && a4 != a1);
	a4 = T("v4");

	xml_attribute a5 = node.insert_attribute_before(T("a5"), a3);
	CHECK(a5 && a5 != a4 && a5 != a3 && a5 != a2 && a5 != a1);
	a5 = T("v5");

	CHECK(child.insert_attribute_before(T("a"), a4) == xml_attribute());

	CHECK_NODE(doc, T("<node a5=\"v5\" a3=\"v3\" a4=\"v4\" a1=\"v1\"><child a2=\"v2\" /></node>"));
}

TEST_XML(dom_node_append_copy_attribute, "<node a1='v1'><child a2='v2'/><child/></node>")
{
	CHECK(xml_node().append_copy(xml_attribute()) == xml_attribute());
	CHECK(xml_node().append_copy(doc.child(T("node")).attribute(T("a1"))) == xml_attribute());
	CHECK(doc.append_copy(doc.child(T("node")).attribute(T("a1"))) == xml_attribute());
	
	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	xml_attribute a1 = node.attribute(T("a1"));
	xml_attribute a2 = child.attribute(T("a2"));

	xml_attribute a3 = node.append_copy(a1);
	CHECK(a3 && a3 != a2 && a3 != a1);

	xml_attribute a4 = node.append_copy(a2);
	CHECK(a4 && a4 != a3 && a4 != a2 && a4 != a1);

	xml_attribute a5 = node.last_child().append_copy(a1);
	CHECK(a5 && a5 != a4 && a5 != a3 && a5 != a2 && a5 != a1);

	CHECK_NODE(doc, T("<node a1=\"v1\" a1=\"v1\" a2=\"v2\"><child a2=\"v2\" /><child a1=\"v1\" /></node>"));

	a3.set_name(T("a3"));
	a3 = T("v3");
	
	a4.set_name(T("a4"));
	a4 = T("v4");
	
	a5.set_name(T("a5"));
	a5 = T("v5");
	
	CHECK_NODE(doc, T("<node a1=\"v1\" a3=\"v3\" a4=\"v4\"><child a2=\"v2\" /><child a5=\"v5\" /></node>"));
}

TEST_XML(dom_node_insert_copy_after_attribute, "<node a1='v1'><child a2='v2'/></node>")
{
	CHECK(xml_node().insert_copy_after(xml_attribute(), xml_attribute()) == xml_attribute());

	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	xml_attribute a1 = node.attribute(T("a1"));
	xml_attribute a2 = child.attribute(T("a2"));

	CHECK(node.insert_copy_after(a1, xml_attribute()) == xml_attribute());
	CHECK(node.insert_copy_after(xml_attribute(), a1) == xml_attribute());
	CHECK(node.insert_copy_after(a2, a2) == xml_attribute());
	
	xml_attribute a3 = node.insert_copy_after(a1, a1);
	CHECK(a3 && a3 != a2 && a3 != a1);

	xml_attribute a4 = node.insert_copy_after(a2, a1);
	CHECK(a4 && a4 != a3 && a4 != a2 && a4 != a1);

	xml_attribute a5 = node.insert_copy_after(a4, a1);
	CHECK(a5 && a5 != a4 && a5 != a3 && a5 != a2 && a5 != a1);

	CHECK(child.insert_copy_after(a4, a4) == xml_attribute());

	CHECK_NODE(doc, T("<node a1=\"v1\" a2=\"v2\" a2=\"v2\" a1=\"v1\"><child a2=\"v2\" /></node>"));

	a3.set_name(T("a3"));
	a3 = T("v3");
	
	a4.set_name(T("a4"));
	a4 = T("v4");
	
	a5.set_name(T("a5"));
	a5 = T("v5");
	
	CHECK_NODE(doc, T("<node a1=\"v1\" a5=\"v5\" a4=\"v4\" a3=\"v3\"><child a2=\"v2\" /></node>"));
}

TEST_XML(dom_node_insert_copy_before_attribute, "<node a1='v1'><child a2='v2'/></node>")
{
	CHECK(xml_node().insert_copy_before(xml_attribute(), xml_attribute()) == xml_attribute());

	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	xml_attribute a1 = node.attribute(T("a1"));
	xml_attribute a2 = child.attribute(T("a2"));

	CHECK(node.insert_copy_before(a1, xml_attribute()) == xml_attribute());
	CHECK(node.insert_copy_before(xml_attribute(), a1) == xml_attribute());
	CHECK(node.insert_copy_before(a2, a2) == xml_attribute());
	
	xml_attribute a3 = node.insert_copy_before(a1, a1);
	CHECK(a3 && a3 != a2 && a3 != a1);

	xml_attribute a4 = node.insert_copy_before(a2, a1);
	CHECK(a4 && a4 != a3 && a4 != a2 && a4 != a1);

	xml_attribute a5 = node.insert_copy_before(a4, a1);
	CHECK(a5 && a5 != a4 && a5 != a3 && a5 != a2 && a5 != a1);

	CHECK(child.insert_copy_before(a4, a4) == xml_attribute());

	CHECK_NODE(doc, T("<node a1=\"v1\" a2=\"v2\" a2=\"v2\" a1=\"v1\"><child a2=\"v2\" /></node>"));

	a3.set_name(T("a3"));
	a3 = T("v3");
	
	a4.set_name(T("a4"));
	a4 = T("v4");
	
	a5.set_name(T("a5"));
	a5 = T("v5");
	
	CHECK_NODE(doc, T("<node a3=\"v3\" a4=\"v4\" a5=\"v5\" a1=\"v1\"><child a2=\"v2\" /></node>"));
}

TEST_XML(dom_node_remove_attribute, "<node a1='v1' a2='v2' a3='v3'><child a4='v4'/></node>")
{
	xml_node().remove_attribute(T("a"));
	xml_node().remove_attribute(xml_attribute());
	
	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	node.remove_attribute(T("a"));
	node.remove_attribute(xml_attribute());
	node.remove_attribute(child.attribute(T("a4")));

	CHECK_NODE(doc, T("<node a1=\"v1\" a2=\"v2\" a3=\"v3\"><child a4=\"v4\" /></node>"));

	node.remove_attribute(T("a1"));
	node.remove_attribute(node.attribute(T("a3")));
	child.remove_attribute(T("a4"));

	CHECK_NODE(doc, T("<node a2=\"v2\"><child /></node>"));
}

TEST_XML(dom_node_append_child, "<node>foo<child/></node>")
{
	CHECK(xml_node().append_child() == xml_node());
	CHECK(doc.child(T("node")).first_child().append_child() == xml_node());
	CHECK(doc.append_child(node_document) == xml_node());
	CHECK(doc.append_child(node_null) == xml_node());
	
	xml_node n1 = doc.child(T("node")).append_child();
	CHECK(n1);
	CHECK(n1.set_name(T("n1")));

	xml_node n2 = doc.child(T("node")).append_child();
	CHECK(n2 && n1 != n2);
	CHECK(n2.set_name(T("n2")));

	xml_node n3 = doc.child(T("node")).child(T("child")).append_child(node_pcdata);
	CHECK(n3 && n1 != n3 && n2 != n3);
	CHECK(n3.set_value(T("n3")));
	
	xml_node n4 = doc.append_child(node_comment);
	CHECK(n4 && n1 != n4 && n2 != n4 && n3 != n4);
	CHECK(n4.set_value(T("n4")));

	CHECK_NODE(doc, T("<node>foo<child>n3</child><n1 /><n2 /></node><!--n4-->"));
}

TEST_XML(dom_node_insert_child_after, "<node>foo<child/></node>")
{
	CHECK(xml_node().insert_child_after(node_element, xml_node()) == xml_node());
	CHECK(doc.child(T("node")).first_child().insert_child_after(node_element, xml_node()) == xml_node());
	CHECK(doc.insert_child_after(node_document, xml_node()) == xml_node());
	CHECK(doc.insert_child_after(node_null, xml_node()) == xml_node());

	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	CHECK(node.insert_child_after(node_element, node) == xml_node());
	CHECK(child.insert_child_after(node_element, node) == xml_node());
	
	xml_node n1 = node.insert_child_after(node_element, child);
	CHECK(n1 && n1 != node && n1 != child);
	CHECK(n1.set_name(T("n1")));

	xml_node n2 = node.insert_child_after(node_element, child);
	CHECK(n2 && n2 != node && n2 != child && n2 != n1);
	CHECK(n2.set_name(T("n2")));

	xml_node n3 = node.insert_child_after(node_pcdata, n2);
	CHECK(n3 && n3 != node && n3 != child && n3 != n1 && n3 != n2);
	CHECK(n3.set_value(T("n3")));

	xml_node n4 = node.insert_child_after(node_pi, node.first_child());
	CHECK(n4 && n4 != node && n4 != child && n4 != n1 && n4 != n2 && n4 != n3);
	CHECK(n4.set_name(T("n4")));

	CHECK(child.insert_child_after(node_element, n3) == xml_node());

	CHECK_NODE(doc, T("<node>foo<?n4?><child /><n2 />n3<n1 /></node>"));
}

TEST_XML(dom_node_insert_child_before, "<node>foo<child/></node>")
{
	CHECK(xml_node().insert_child_before(node_element, xml_node()) == xml_node());
	CHECK(doc.child(T("node")).first_child().insert_child_before(node_element, xml_node()) == xml_node());
	CHECK(doc.insert_child_before(node_document, xml_node()) == xml_node());
	CHECK(doc.insert_child_before(node_null, xml_node()) == xml_node());

	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	CHECK(node.insert_child_before(node_element, node) == xml_node());
	CHECK(child.insert_child_before(node_element, node) == xml_node());
	
	xml_node n1 = node.insert_child_before(node_element, child);
	CHECK(n1 && n1 != node && n1 != child);
	CHECK(n1.set_name(T("n1")));

	xml_node n2 = node.insert_child_before(node_element, child);
	CHECK(n2 && n2 != node && n2 != child && n2 != n1);
	CHECK(n2.set_name(T("n2")));

	xml_node n3 = node.insert_child_before(node_pcdata, n2);
	CHECK(n3 && n3 != node && n3 != child && n3 != n1 && n3 != n2);
	CHECK(n3.set_value(T("n3")));

	xml_node n4 = node.insert_child_before(node_pi, node.first_child());
	CHECK(n4 && n4 != node && n4 != child && n4 != n1 && n4 != n2 && n4 != n3);
	CHECK(n4.set_name(T("n4")));

	CHECK(child.insert_child_before(node_element, n3) == xml_node());

	CHECK_NODE(doc, T("<node><?n4?>foo<n1 />n3<n2 /><child /></node>"));
}

TEST_XML(dom_node_remove_child, "<node><n1/><n2/><n3/><child><n4/></child></node>")
{
	xml_node().remove_child(T("a"));
	xml_node().remove_child(xml_node());
	
	xml_node node = doc.child(T("node"));
	xml_node child = node.child(T("child"));

	node.remove_child(T("a"));
	node.remove_child(xml_node());
	node.remove_child(child.child(T("n4")));

	CHECK_NODE(doc, T("<node><n1 /><n2 /><n3 /><child><n4 /></child></node>"));

	node.remove_child(T("n1"));
	node.remove_child(node.child(T("n3")));
	child.remove_child(T("n4"));

	CHECK_NODE(doc, T("<node><n2 /><child /></node>"));
}

TEST_XML(dom_node_append_copy, "<node>foo<child/></node>")
{
	CHECK(xml_node().append_copy(xml_node()) == xml_node());
	CHECK(doc.child(T("node")).first_child().append_copy(doc.child(T("node"))) == xml_node());
	CHECK(doc.append_copy(doc) == xml_node());
	CHECK(doc.append_copy(xml_node()) == xml_node());
	
	xml_node n1 = doc.child(T("node")).append_copy(doc.child(T("node")).first_child());
	CHECK(n1);
	CHECK_STRING(n1.value(), T("foo"));
	CHECK_NODE(doc, T("<node>foo<child />foo</node>"));

	xml_node n2 = doc.child(T("node")).append_copy(doc.child(T("node")).child(T("child")));
	CHECK(n2 && n2 != n1);
	CHECK_STRING(n2.name(), T("child"));
	CHECK_NODE(doc, T("<node>foo<child />foo<child /></node>"));

	xml_node n3 = doc.child(T("node")).child(T("child")).append_copy(doc.child(T("node")).first_child());
	CHECK(n3 && n3 != n1 && n3 != n2);
	CHECK_STRING(n3.value(), T("foo"));
	CHECK_NODE(doc, T("<node>foo<child>foo</child>foo<child /></node>"));
}

TEST_XML(dom_node_insert_copy_after, "<node>foo<child/></node>")
{
	CHECK(xml_node().insert_copy_after(xml_node(), xml_node()) == xml_node());
	CHECK(doc.child(T("node")).first_child().insert_copy_after(doc.child(T("node")), doc.child(T("node"))) == xml_node());
	CHECK(doc.insert_copy_after(doc, doc) == xml_node());
	CHECK(doc.insert_copy_after(xml_node(), doc.child(T("node"))) == xml_node());
	CHECK(doc.insert_copy_after(doc.child(T("node")), xml_node()) == xml_node());
	
	xml_node n1 = doc.child(T("node")).insert_copy_after(doc.child(T("node")).child(T("child")), doc.child(T("node")).first_child());
	CHECK(n1);
	CHECK_STRING(n1.name(), T("child"));
	CHECK_NODE(doc, T("<node>foo<child /><child /></node>"));

	xml_node n2 = doc.child(T("node")).insert_copy_after(doc.child(T("node")).first_child(), doc.child(T("node")).last_child());
	CHECK(n2 && n2 != n1);
	CHECK_STRING(n2.value(), T("foo"));
	CHECK_NODE(doc, T("<node>foo<child /><child />foo</node>"));

	xml_node n3 = doc.child(T("node")).insert_copy_after(doc.child(T("node")).first_child(), doc.child(T("node")).first_child());
	CHECK(n3 && n3 != n1 && n3 != n2);
	CHECK_STRING(n3.value(), T("foo"));
	CHECK_NODE(doc, T("<node>foofoo<child /><child />foo</node>"));
}

TEST_XML(dom_node_insert_copy_before, "<node>foo<child/></node>")
{
	CHECK(xml_node().insert_copy_before(xml_node(), xml_node()) == xml_node());
	CHECK(doc.child(T("node")).first_child().insert_copy_before(doc.child(T("node")), doc.child(T("node"))) == xml_node());
	CHECK(doc.insert_copy_before(doc, doc) == xml_node());
	CHECK(doc.insert_copy_before(xml_node(), doc.child(T("node"))) == xml_node());
	CHECK(doc.insert_copy_before(doc.child(T("node")), xml_node()) == xml_node());
	
	xml_node n1 = doc.child(T("node")).insert_copy_before(doc.child(T("node")).child(T("child")), doc.child(T("node")).first_child());
	CHECK(n1);
	CHECK_STRING(n1.name(), T("child"));
	CHECK_NODE(doc, T("<node><child />foo<child /></node>"));

	xml_node n2 = doc.child(T("node")).insert_copy_before(doc.child(T("node")).first_child(), doc.child(T("node")).last_child());
	CHECK(n2 && n2 != n1);
	CHECK_STRING(n2.name(), T("child"));
	CHECK_NODE(doc, T("<node><child />foo<child /><child /></node>"));

	xml_node n3 = doc.child(T("node")).insert_copy_before(doc.child(T("node")).first_child().next_sibling(), doc.child(T("node")).first_child());
	CHECK(n3 && n3 != n1 && n3 != n2);
	CHECK_STRING(n3.value(), T("foo"));
	CHECK_NODE(doc, T("<node>foo<child />foo<child /><child /></node>"));
}

TEST_XML(dom_node_copy_recursive, "<node>foo<child/></node>")
{
	doc.child(T("node")).append_copy(doc.child(T("node")));
	CHECK_NODE(doc, T("<node>foo<child /><node>foo<child /></node></node>"));
}

TEST_XML(dom_node_copy_crossdoc, "<node/>")
{
	xml_document newdoc;
	newdoc.append_copy(doc.child(T("node")));
	CHECK_NODE(doc, T("<node />"));
	CHECK_NODE(newdoc, T("<node />"));
}

TEST_XML_FLAGS(dom_node_copy_types, "<root><?xml version='1.0'?><?pi value?><!--comment--><node id='1'>pcdata<![CDATA[cdata]]></node></root>", parse_default | parse_pi | parse_comments | parse_declaration)
{
	doc.append_copy(doc.child(T("root")));
	CHECK_NODE(doc, T("<root><?xml version=\"1.0\"?><?pi value?><!--comment--><node id=\"1\">pcdata<![CDATA[cdata]]></node></root><root><?xml version=\"1.0\"?><?pi value?><!--comment--><node id=\"1\">pcdata<![CDATA[cdata]]></node></root>"));
}