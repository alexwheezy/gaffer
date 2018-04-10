//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2016, John Haddon. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#include "GafferBindings/NodeBinding.h"

#include "Gaffer/Context.h"

#include "GafferUI/Gadget.h"

#include "GafferSceneUI/TransformTool.h"
#include "GafferSceneUIBindings/TransformToolBinding.h"

using namespace std;
using namespace boost::python;
using namespace Gaffer;
using namespace GafferScene;
using namespace GafferSceneUI;

namespace
{

ScenePlugPtr scene( const TransformTool::Selection &s )
{
	return boost::const_pointer_cast<ScenePlug>( s.scene );
}

std::string path( const TransformTool::Selection &s )
{
	std::string result;
	ScenePlug::pathToString( s.path, result );
	return result;
}

ContextPtr context( const TransformTool::Selection &s )
{
	return boost::const_pointer_cast<Context>( s.context );
}

ScenePlugPtr upstreamScene( const TransformTool::Selection &s )
{
	return boost::const_pointer_cast<ScenePlug>( s.upstreamScene );
}

std::string upstreamPath( const TransformTool::Selection &s )
{
	std::string result;
	ScenePlug::pathToString( s.upstreamPath, result );
	return result;
}

ContextPtr upstreamContext( const TransformTool::Selection &s )
{
	return boost::const_pointer_cast<Context>( s.context );
}

TransformPlugPtr transformPlug( const TransformTool::Selection &s )
{
	return s.transformPlug;
}

} // namespace

void GafferSceneUIBindings::bindTransformTool()
{

	scope s = GafferBindings::NodeClass<TransformTool>( NULL, no_init )
		.def( "selection", &TransformTool::selection, return_value_policy<copy_const_reference>() )
		.def( "handlesTransform", &TransformTool::handlesTransform )
	;

	class_<TransformTool::Selection>( "Selection", no_init )

		.add_property( "scene", &scene )
		.add_property( "path", &path )
		.add_property( "context", &context )

		.add_property( "upstreamScene", &upstreamScene )
		.add_property( "upstreamPath", &upstreamPath )
		.add_property( "upstreamContext", &upstreamContext )

		.add_property( "transformPlug", &transformPlug )
		.def_readonly( "transformSpace", &TransformTool::Selection::transformSpace )

	;

	enum_<TransformTool::Orientation>( "Orientation" )
		.value( "Local", TransformTool::Local )
		.value( "Parent", TransformTool::Parent )
		.value( "World", TransformTool::World )
	;

}
