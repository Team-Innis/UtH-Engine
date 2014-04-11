#pragma once
#ifndef ENUMS_TMX_UTH_H
#define ENUMS_TMX_UTH_H

namespace uth
{
	namespace TMX
	{
		// What i wouldn't give to use enum classes

		namespace Orientation
		{
			enum Orientation
			{
				UNKNOWN,
				ORTHOGONAL,
				ISOMETRIC,
				STAGGERED
			};
		}

		namespace Encryption
		{
			enum Encryption
			{
				NONE,
				BASE64,
				CSV
			};
		}

		namespace Compression
		{
			enum Compression
			{
				NONE,
				ZLIB,
				GZIP
			};
		}
	}
}

#endif