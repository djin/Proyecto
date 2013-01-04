//////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008-2013, Shane Liesegang
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the copyright holder nor the names of any
//       contributors may be used to endorse or promote products derived from
//       this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "../Input/MouseInput.h"
#include "../Util/StringUtil.h"

class GwenRenderer;

//singleton shortcut
#define theUI UserInterface::GetInstance()

typedef void* AngelUIHandle;


class UserInterface : public MouseListener 
{
public:
    /**
	 * Used to access the singleton instance of this class. As a shortcut,
	 *  you can just use "theUI".
	 *
	 * @return The singleton
	 */
	static UserInterface& GetInstance();
    
    void Render();
    
	virtual void MouseMotionEvent(Vec2i screenCoordinates);
	virtual void MouseDownEvent(Vec2i screenCoordinates, MouseButtonInput button);
	virtual void MouseUpEvent(Vec2i screenCoordinates, MouseButtonInput button);
	virtual void MouseWheelEvent(int position);
    
	void HandleKey(int key, bool down);
    void HandleCharacter(wchar_t chr);
    
    void Shutdown();
    
    void RemoveUIElement(AngelUIHandle element);
    AngelUIHandle AddButton(const String& label, Vec2i position, void (*callback)(), bool center = false, const String& font="", Vec2i padding=Vec2i(10, 10));
	AngelUIHandle ShowChoiceBox(const String& choiceLabel, const StringList& labels, void (*callback)(int), const String& font="", Vec2i padding=Vec2i(10, 10), bool modal=true);
    
    
protected:
    UserInterface();
	~UserInterface();
    
    static UserInterface* s_UserInterface;

private:
    GwenRenderer* _renderer;

	Vec2i _mousePosition;
    
    std::set<AngelUIHandle> _elements;
    std::vector<AngelUIHandle> _deferredRemoves;
    
    bool _locked;
};