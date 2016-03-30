/*!
 *  @file		AppleMIDI_EndSession.h
 *  Project		Arduino AppleMIDI Library
 *	@brief		AppleMIDI Library for the Arduino
 *	Version		0.3
 *  @author		lathoub
 *	@date		04/04/14
 *  License		GPL
 */

#pragma once

#include "AppleMidi_Settings.h"
#include "AppleMidi_Defs.h"
#include "AppleMidi_Util.h"

BEGIN_APPLEMIDI_NAMESPACE

typedef struct AppleMIDI_EndSession {

	uint8_t		signature[2];
	uint8_t		command[2];
	uint32_t	version;
	uint32_t	initiatorToken;
	uint32_t	ssrc;


	inline AppleMIDI_EndSession()
	{
		init();
	}

	void init()
	{
		memcpy(signature, amSignature, sizeof(amSignature));
		memcpy(command, amEndSession, sizeof(amEndSession));
	}

	void write(UDP* udp)
	{
		udp->beginPacket(udp->remoteIP(), udp->remotePort());

		udp->write(signature, sizeof(signature));
		udp->write(command,   sizeof(command));
		udp->write(AppleMIDI_Util::toBuffer(version), sizeof(version));
		udp->write(AppleMIDI_Util::toBuffer(initiatorToken), sizeof(initiatorToken));
		udp->write(AppleMIDI_Util::toBuffer(ssrc), sizeof(ssrc));

		udp->endPacket();
		udp->flush(); // Waits for the transmission of outgoing serial data to complete

#if (APPLEMIDI_DEBUG)
		Serial.println("< End Session");
#endif
	}

} EndSession_t;

END_APPLEMIDI_NAMESPACE
