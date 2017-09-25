#include "util.hpp"

namespace  util {

	std::string UnicodeToUTF8(unsigned int codepoint)
	{
		std::string out;

		if (codepoint <= 0x7f)
			out.append(1, static_cast<char>(codepoint));
		else if (codepoint <= 0x7ff)
		{
			out.append(1, static_cast<char>(0xc0 | ((codepoint >> 6) & 0x1f)));
			out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
		}
		else if (codepoint <= 0xffff)
		{
			out.append(1, static_cast<char>(0xe0 | ((codepoint >> 12) & 0x0f)));
			out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
			out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
		}
		else
		{
			out.append(1, static_cast<char>(0xf0 | ((codepoint >> 18) & 0x07)));
			out.append(1, static_cast<char>(0x80 | ((codepoint >> 12) & 0x3f)));
			out.append(1, static_cast<char>(0x80 | ((codepoint >> 6) & 0x3f)));
			out.append(1, static_cast<char>(0x80 | (codepoint & 0x3f)));
		}
		return out;
	}

	/*
	glm::vec4 Player::TraceRay(glm::vec3 posit, glm::vec3 dir, int max, bool last)
	{
		glm::vec3 vox = glm::floor(posit);
		glm::vec3 next(max, max, max);
		glm::vec3 delta(max, max, max);
		glm::vec3 step(0, 0, 0);
		glm::vec3 lastVox(-1);
		lastBlock = glm::vec4(-1);

		if (world->getCube(vox[0], vox[1], vox[2]) > 0) {
			if (last)
				return glm::vec4(-1);
			return glm::vec4(vox[0], vox[1], vox[2], 0);
		}

		for (int i = 0; i < 3; ++i) {
			if (dir[i] < 0) {
				step[i] = -1;
				delta[i] = step[i] / dir[i];
				next[i] = (vox[i] - posit[i]) / dir[i];
			} else if (dir[i] != 0) {
				step[i] = 1;
				delta[i] = step[i] / dir[i];
				next[i] = ((vox[i] + 1) - posit[i]) / dir[i];
			}
		}

		int nb = 0;
		while (nb < max) {
			lastVox = vox;
			// Perform DDA
			int side = 0;
			for (int i = 1; i < 3; ++i) {
				if (next[side] > next[i]) {
					side = i;
				}
			}
			next[side] += delta[side];
			vox[side] += step[side];

			// Sample volume data at calculated position and make collision calculations
			if (world->getCube(vox[0], vox[1], vox[2]) > 0) {
				lastBlock = glm::vec4(lastVox, side);
				if (last)
					return glm::vec4(lastVox, side);
				return glm::vec4(vox[0], vox[1], vox[2], side);
			}
			nb++;
		}
		return glm::vec4(-1); // No voxel found
	} */

}