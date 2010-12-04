/*
 * Copyright (C) 2008 Martin Willi
 * Hochschule fuer Technik Rapperswil
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include "sqlite_plugin.h"

#include <library.h>
#include "sqlite_database.h"

typedef struct private_sqlite_plugin_t private_sqlite_plugin_t;

/**
 * private data of sqlite_plugin
 */
struct private_sqlite_plugin_t {

	/**
	 * public functions
	 */
	sqlite_plugin_t public;
};

METHOD(plugin_t, destroy, void,
	private_sqlite_plugin_t *this)
{
	lib->db->remove_database(lib->db,
							 (database_constructor_t)sqlite_database_create);
	free(this);
}

/*
 * see header file
 */
plugin_t *sqlite_plugin_create()
{
	private_sqlite_plugin_t *this;

	INIT(this,
		.public = {
			.plugin = {
				.destroy = _destroy,
			},
		},
	);

	lib->db->add_database(lib->db,
						  (database_constructor_t)sqlite_database_create);

	return &this->public.plugin;
}

