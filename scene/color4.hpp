///============================================================================
//	Johns Hopkins University Engineering Programs for Professionals
//	605.667 Computer Graphics and 605.767 Applied Computer Graphics
//	Instructor:	Brian Russin
//
//	Original Author: David W. Nesbitt
//	Modified by Kat Moormann
//	File:    color4.hpp
//	Purpose: Color structure with RGBA. Supports adding and blending colors.
//           Includes clamping to [0,1] range.
//
//  Modified again by Kat Moormann Friday May 01 2026
//============================================================================

#ifndef __SCENE_COLOR4_HPP__
#define __SCENE_COLOR4_HPP__

#include "scene/color3.hpp"

#include <cstdint>

namespace cg
{
/**
 * This structure stores a color using:
 * - Red (r)
 * - Green (g)
 * - Blue (b)
 * - Alpha (a)
 *
 * Each value is usually between:
 * 0.0 = no color
 * 1.0 = full intensity
 *
 * Example:
 * (1.0, 0.0, 0.0, 1.0) = fully visible red
 * (0.0, 1.0, 0.0, 1.0) = fully visible green
 * (0.0, 0.0, 1.0, 1.0) = fully visible blue
 *
 * Alpha controls transparency:
 * 1.0 = fully visible
 * 0.0 = fully transparent
 *
 * IMPORTANT:
 * This class does NOT automatically force values to stay between
 * 0.0 and 1.0 after every math operation.
 *
 * That means colors can temporarily become values like:
 * (1.5, 0.3, 2.0)
 *
 * This is intentional for performance reasons.
 *
 * Why?
 * In ray tracing, the program may perform millions of color calculations
 * while light bounces around a scene.
 *
 * Automatically fixing/clamping the values after every calculation
 * would slow things down.
 *
 * Instead:
 * The program waits until the final result is needed, then calls clamp()
 * to force values back into the valid range.
 */
struct Color4
{
    float r, g, b, a;

    /**
     * Default constructor
     * 
     * Creates a color with all values set to 0
     * This usually means black and fully transparent
     */
    Color4(void);

    /**
     * Constructor. Set RGB to specified values. Clamps to range [0.0, 1.0]
     * @param	red     Red intensity
     * @param	green   Green intensity
     * @param	blue    Blue intensity
     * @param	alpha   Alpha value for blending
     */
    Color4(float red, float green, float blue, float alpha);

    /**
     * Constructor with RGB. Sets A to 1.0. Clamps to range [0.0, 1.0]
     * @param	red     Red intensity
     * @param	green   Green intensity
     * @param	blue    Blue intensity
     */
    Color4(float red, float green, float blue);

    /**
     * Constructor from a Color3. Sets A to 1.0f. Should be no need to clamp
     * since Color3 must have been clamped to [0,1] range.
     * @param c Color assigned to member.
     */
    Color4(const Color3 &c);

    /**
     * Copy constructor.
     * @param c Color assigned to member.
     */
    Color4(const Color4 &c);

    /**
     * Assignment operator.
     * @param  c Color to assign to the object.
     * @return Returns the address of the member data.
     */
    Color4 &operator=(const Color4 &c);

    /**
     *	Set the color to the specified RGB values.
     * @param	ir		Red intensity
     * @param	ig		Green intensity
     * @param	ib		Blue intensity
     */
    void set(float ir, float ig, float ib, float ia);

    /**
     * Get the red value in the range 0-255
     * @return  Returns red value as a [0-255] value
     */
    uint8_t r_byte() const;

    /**
     * Get the green value in the range 0-255
     * @return  Returns green value as a [0-255] value
     */
    uint8_t g_byte() const;

    /**
     * Get the blue value in the range 0-255
     * @return  Returns blue value as a [0-255] value
     */
    uint8_t b_byte() const;

    /**
     * Converts the red value from:
     * 0.0–1.0
     *
     * into:
     * 0–255
     *
     * This is useful when sending colors to images/screens.
     */
    uint8_t a_byte() const;

    /**
     * Multiplication operator: Multiplies the color by another color
     */
    Color4 operator*(const Color4 &color) const;

    /**
     * Multiplication operator: Multiplies the color by another color (RGB only).
     * Ignores alpha.
     * @return  Returns RGB color
     */
    Color3 operator*(const Color3 &color) const;

    /**
     * Makes the color brighter or darker
     * by multiplying it by a number.
     *
     * Example:
     * color * 0.5 = darker
     * color * 2.0 = brighter
     */
    Color4 operator*(float factor);

    /**
     * Adds another color to the current color. Clamps to the valid range.
     */
    Color4 &operator+=(const Color4 &color);

    /**
     * Creates a new color that is the current color plus the
     * specified color.
     * Often used when combining light contributions
     * @param   c  Color to add to the current color.
     * @return  Returns the resulting color.
     */
    Color4 operator+(const Color4 &c) const;

    /**
     * Makes sure color values stay between 0.0 and 1.0.
     *
     * Example:
     * 1.5 becomes 1.0
     * -0.2 becomes 0.0
     *
     * This prevents invalid color values.
     */
    void clamp();
};

} // namespace cg

#endif
