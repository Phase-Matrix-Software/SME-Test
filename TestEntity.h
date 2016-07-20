/* 
 * File:   TestEntity.h
 * Author: Sam
 *
 * Created on 18 July 2016, 19:43
 */

#ifndef TESTENTITY_H
#define	TESTENTITY_H

#include <SME_entity.h>

class TestEntity : public SME::Level::Entity {
public:
    void update();
};

SME_REGISTER_ENTITY(TestEntity);

#endif	/* TESTENTITY_H */

