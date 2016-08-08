/* 
 * File:   TestAttachment.h
 * Author: Sam
 *
 * Created on 23 July 2016, 16:27
 */

#ifndef TESTATTACHMENT_H
#define	TESTATTACHMENT_H

#include <SME_attachment.h>

struct TestAttachment : public SME::Level::Entity::Attachment {
    TestAttachment(SME::Level::Entity::Entity *entity);
    ~TestAttachment();
    
    void onPosChanged(glm::vec3 pos);
    void onVelChanged(glm::vec3 vel);
    void onRotChanged(glm::vec3 rot);
    void onUpdate();
};

#endif	/* TESTATTACHMENT_H */

