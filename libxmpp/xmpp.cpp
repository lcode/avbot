/*
 * Copyright (C) 2013  微蔡 <microcai@fedoraproject.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "xmpp.h"
#include "xmpp_impl.h"

xmpp::xmpp(boost::asio::io_service& asio, std::string xmppuser, std::string xmpppasswd, std::string xmppserver)
{
	if (!xmppuser.empty() && !xmpppasswd.empty())
		impl.reset(new XMPP::xmpp_impl(asio, xmppuser, xmpppasswd, xmppserver));
}

void xmpp::join(std::string roomjid)
{
	if (impl)
		impl->join(roomjid);
}

xmpp::~xmpp()
{
}

void xmpp::on_room_message(boost::function<void (std::string xmpproom, std::string who, std::string message)> cb)
{
	if (impl)
		impl->on_room_message(cb);
}

void xmpp::send_room_message(std::string xmpproom, std::string message)
{
	if (impl)
		impl->send_room_message(xmpproom, message);
}
