#include "AxesNode.hpp"

#include <osg/PositionAttitudeTransform>
#include <osg/Point>
#include <osg/LineWidth>
#include <osgText/Text>
#include <assert.h>
#include <iostream>

namespace vizkit3d
{
    ::osg::Node* AxesNode::create(float scale)
    {
        ::osg::PositionAttitudeTransform *transform = new ::osg::PositionAttitudeTransform();
        ::osg::Geode *geode = new ::osg::Geode;
        transform->addChild(geode);
        transform->setScale(::osg::Vec3(scale,scale,scale));

        ::osg::Geometry* geom = new ::osg::Geometry;
        ::osg::Vec3Array* v = new ::osg::Vec3Array;
        geom->setVertexArray(v); 
        ::osg::Vec4Array* c = new ::osg::Vec4Array;
        geom->setColorArray(c);
        geom->setColorBinding(::osg::Geometry::BIND_PER_VERTEX);

        float arrow[][2] = {
            {0.0, 0.0},
            {1.0, 0.0},
            {1.0, 0.0},
            {0.8, 0.1},
            {1.0, 0.0},
            {0.8, -0.1} };

        int axis[][2] = {
            {0,1},
            {1,0},
            {2,1} };

        float color[][3] = {
            {0.9, 0.1, 0.1},
            {0.1, 0.9, 0.1},
            {0.1, 0.1, 0.9} };

        for(int a=0;a<3;a++) 
        {
            for(int i=0;i<6;i++)
            {
                ::osg::Vec3 pos(0.0,0.0,0.0);
                pos[axis[a][0]] = arrow[i][0];
                pos[axis[a][1]] = arrow[i][1];
                v->push_back( pos );
                c->push_back( ::osg::Vec4( color[a][0], color[a][1], color[a][2], 1.0 ) );
            }
        }
        geom->getOrCreateStateSet()->setAttribute( new ::osg::LineWidth(2.0f),::osg::StateAttribute::ON );
        geom->addPrimitiveSet(new ::osg::DrawArrays(::osg::PrimitiveSet::LINES, 0,v->size()));

        ::osg::StateSet* stategeode = geode->getOrCreateStateSet();
        stategeode->setMode( GL_LIGHTING, ::osg::StateAttribute::OFF );
        geode->addDrawable(geom);

        // add label
        ::osgText::Text *text= new ::osgText::Text;
        text->setText("X");
        text->setCharacterSize(0.1);
        text->setPosition(::osg::Vec3d(0.4,0.0,0.02));
        text->setAxisAlignment(osgText::Text::XZ_PLANE);
        text->setColor( osg::Vec4(0.9f, 0.1f, 0.1f, 1.0f) );
        geode->addDrawable(text);

        text= new ::osgText::Text;
        text->setText("Y");
        text->setCharacterSize(0.1);
        text->setPosition(::osg::Vec3d(0,0.4,0.02));
        text->setAxisAlignment(osgText::Text::YZ_PLANE);
        text->setColor( osg::Vec4(0.1f, 0.9f, 0.1f, 1.0f) );
        geode->addDrawable(text);

        text= new ::osgText::Text;
        text->setText("Z");
        text->setCharacterSize(0.1);
        text->setPosition(::osg::Vec3d(0,0.01,0.4));
        text->setAxisAlignment(osgText::Text::YZ_PLANE);
        text->setColor( osg::Vec4(0.1f, 0.1f, 0.9f, 1.0f) );
        geode->addDrawable(text);

        return (::osg::Node*)transform;
    }

    void AxesNode::setPosition(::osg::Node* axes,const ::osg::Vec3 &position)
    {
        assert(axes);
        ::osg::Transform *transform = axes->asTransform();
        assert(transform);
        ::osg::PositionAttitudeTransform *p = transform->asPositionAttitudeTransform();
        assert(p);
        p->setPosition(position);
    }
}
