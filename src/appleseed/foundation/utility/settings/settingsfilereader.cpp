
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010 Francois Beaune
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

// Interface header.
#include "settingsfilereader.h"

// appleseed.foundation headers.
#include "foundation/utility/containers/dictionary.h"
#include "foundation/utility/log.h"
#include "foundation/utility/xercesc.h"

// Xerces-C++ headers.
#include "xercesc/dom/DOM.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/util/XMLException.hpp"

// Standard headers.
#include <memory>
#include <string>

using namespace std;
using namespace xercesc;

namespace foundation
{

//
// SettingsFileReader class implementation.
//

// Constructor.
SettingsFileReader::SettingsFileReader(Logger& logger)
  : m_logger(logger)
{
}

namespace
{
    void build_dictionary(const DOMNode* node, Dictionary& dictionary)
    {
        assert(node);

        const basic_string<XMLCh> name_attribute_name = transcode("name");
        const basic_string<XMLCh> value_attribute_name = transcode("value");

        node = node->getFirstChild();

        while (node)
        {
            if (node->getNodeType() == DOMNode::ELEMENT_NODE)
            {
                if (transcode(node->getNodeName()) == "parameters")
                {
                    DOMNamedNodeMap* attributes = node->getAttributes();
                    DOMNode* name_attribute = attributes->getNamedItem(name_attribute_name.c_str());

                    Dictionary child_dictionary;
                    build_dictionary(node, child_dictionary);

                    dictionary.insert(
                        transcode(name_attribute->getNodeValue()),
                        child_dictionary);
                }
                else
                {
                    DOMNamedNodeMap* attributes = node->getAttributes();
                    DOMNode* name_attribute = attributes->getNamedItem(name_attribute_name.c_str());
                    DOMNode* value_attribute = attributes->getNamedItem(value_attribute_name.c_str());

                    dictionary.insert(
                        transcode(name_attribute->getNodeValue()),
                        transcode(value_attribute->getNodeValue()));
                }
            }

            node = node->getNextSibling();
        }
    }
}

// Read a settings file from disk.
bool SettingsFileReader::read(
    const char*     settings_filename,
    const char*     schema_filename,
    Dictionary&     settings)
{
    // Initialize Xerces-C++.
    XercesCContext xerces_context(m_logger);
    if (!xerces_context.is_initialized())
        return false;

    // Create the DOM parser.
    auto_ptr<XercesDOMParser> parser(new XercesDOMParser());
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setDoNamespaces(true);
    parser->setDoSchema(true);
    parser->setValidationSchemaFullChecking(false);
    parser->setExternalNoNamespaceSchemaLocation(schema_filename);

    // Create the error handler.
    auto_ptr<ErrorLogger> error_handler(new ErrorLogger(m_logger, settings_filename));
    parser->setErrorHandler(error_handler.get());

    // Parse the settings file.
    try
    {
        parser->parse(settings_filename);
    }
    catch (const XMLException&)
    {
        return false;
    }
    catch (const DOMException&)
    {
        return false;
    }

    // If an error occurred, we won't have a document. Bail out.
    const DOMDocument* document = parser->getDocument();
    if (!document)
        return false;

    // Build a dictionary out of the XML document.
    build_dictionary(document->getFirstChild(), settings);

    return true;
}

}   // namespace foundation
