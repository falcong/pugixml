#ifndef PUGIXML_NO_XPATH

#include "common.hpp"

#include "helpers.hpp"

TEST_XML(xpath_api_select_nodes, "<node><head/><foo/><foo/><tail/></node>")
{
	doc.precompute_document_order();

	xpath_node_set ns1 = doc.select_nodes("node/foo");

	xpath_query q("node/foo");
	xpath_node_set ns2 = doc.select_nodes(q);

	CHECK(ns1.size() == 2 && ns1[0].node().document_order() == 4 && ns1[1].node().document_order() == 5);
	CHECK(ns2.size() == 2 && ns2[0].node().document_order() == 4 && ns2[1].node().document_order() == 5);
}

TEST_XML(xpath_api_select_single_node, "<node><head/><foo/><foo/><tail/></node>")
{
	doc.precompute_document_order();

	xpath_node n1 = doc.select_single_node("node/foo");

	xpath_query q("node/foo");
	xpath_node n2 = doc.select_single_node(q);

	CHECK(n1.node().document_order() == 4);
	CHECK(n2.node().document_order() == 4);

	xpath_node n3 = doc.select_single_node("node/bar");
	
	CHECK(!n3);

	xpath_node n4 = doc.select_single_node("node/head/following-sibling::foo");
	xpath_node n5 = doc.select_single_node("node/tail/preceding-sibling::foo");
	
	CHECK(n4.node().document_order() == 4);
	CHECK(n5.node().document_order() == 4);
}

TEST(xpath_api_exception_what)
{
	try
	{
		xpath_query q("");
	}
	catch (const xpath_exception& e)
	{
		CHECK(e.what()[0] != 0);
	}
}

TEST_XML(xpath_api_node_bool_ops, "<node attr='value'/>")
{
	generic_bool_ops_test(doc.select_single_node("node"));
	generic_bool_ops_test(doc.select_single_node("node/@attr"));
}

TEST_XML(xpath_api_node_eq_ops, "<node attr='value'/>")
{
	generic_eq_ops_test(doc.select_single_node("node"), doc.select_single_node("node/@attr"));
}

TEST_XML(xpath_api_node_accessors, "<node attr='value'/>")
{
	xpath_node null;
	xpath_node node = doc.select_single_node("node");
	xpath_node attr = doc.select_single_node("node/@attr");

	CHECK(!null.node());
	CHECK(!null.attribute());
	CHECK(!null.parent());

	CHECK(node.node() == doc.child("node"));
	CHECK(!node.attribute());
	CHECK(node.parent() == doc);

	CHECK(!attr.node());
	CHECK(attr.attribute() == doc.child("node").attribute("attr"));
	CHECK(attr.parent() == doc.child("node"));
}

inline void xpath_api_node_accessors_helper(const xpath_node_set& set)
{
	CHECK(set.size() == 2);
	CHECK(set.type() == xpath_node_set::type_sorted);
	CHECK(!set.empty());
	CHECK_STRING(set[0].node().name(), "foo");
	CHECK_STRING(set[1].node().name(), "foo");
	CHECK(!set[2]);
	CHECK(set.first() == set[0]);
	CHECK(set.begin() + 2 == set.end());
	CHECK(set.begin()[0] == set[0] && set.begin()[1] == set[1]);
}

TEST_XML(xpath_api_nodeset_accessors, "<node><foo/><foo/></node>")
{
	xpath_node_set null;
	CHECK(null.size() == 0);
	CHECK(null.type() == xpath_node_set::type_unsorted);
	CHECK(null.empty());
	CHECK(!null[0]);
	CHECK(!null.first());
	CHECK(null.begin() == null.end());

	xpath_node_set set = doc.select_nodes("node/foo");
	xpath_api_node_accessors_helper(set);

	xpath_node_set copy = set;
	xpath_api_node_accessors_helper(copy);

	xpath_node_set assigned;
	assigned = set;
	xpath_api_node_accessors_helper(assigned);

	xpath_node_set nullcopy = null;
}

TEST_XML(xpath_api_evaluate, "<node attr='3'/>")
{
	xpath_query q("node/@attr");

	CHECK(q.evaluate_boolean(doc));
	CHECK(q.evaluate_number(doc) == 3);
	CHECK(q.evaluate_string(doc) == "3");

	xpath_node_set ns = q.evaluate_node_set(doc);
	CHECK(ns.size() == 1 && ns[0].attribute() == doc.child("node").attribute("attr"));
}

TEST(xpath_api_evaluate_node_set)
{
	try
	{
		xpath_query q("1");

		q.evaluate_node_set(xml_node());
	}
	catch (const xpath_exception&)
	{
	}
}

#endif
