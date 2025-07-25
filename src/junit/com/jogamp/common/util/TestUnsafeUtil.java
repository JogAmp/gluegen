/**
 * Copyright 2025 JogAmp Community. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 *    1. Redistributions of source code must retain the above copyright notice, this list of
 *       conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above copyright notice, this list
 *       of conditions and the following disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY JogAmp Community ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL JogAmp Community OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those of the
 * authors and should not be interpreted as representing official policies, either expressed
 * or implied, of JogAmp Community.
 */

package com.jogamp.common.util;

import java.nio.ByteBuffer;
import java.security.PrivilegedAction;

import org.junit.Assert;
import org.junit.BeforeClass;
import org.junit.Test;

import com.jogamp.common.nio.Buffers;
import com.jogamp.common.os.Platform;
import com.jogamp.junit.util.SingletonJunitCase;

import org.junit.FixMethodOrder;
import org.junit.runners.MethodSorters;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class TestUnsafeUtil extends SingletonJunitCase {

    @BeforeClass
    public static void init() {
        Platform.initSingleton();
    }

    @Test
    public void testWithoutIllegalAccessLogger00()  {
        if( ! UnsafeUtil.hasIllegalAccessLoggerAccess() ) {
            return;
        }
        final Boolean res = UnsafeUtil.doWithoutIllegalAccessLogger(new PrivilegedAction<Boolean>() {
                    @Override
                    public Boolean run() {
                        return Boolean.TRUE;
                    }
                });
        Assert.assertEquals(Boolean.TRUE, res);
    }

    @Test
    public void test01()  {
        final ByteBuffer bb = Buffers.newDirectByteBuffer(100);
        final long a0 = UnsafeUtil.getDirectBufferAddress(bb);
        final long a1 = Buffers.getDirectBufferAddress(bb);
        Assert.assertEquals(a0, a1);
    }

    public static void main(final String args[]) {
        final String tstname = TestUnsafeUtil.class.getName();
        org.junit.runner.JUnitCore.main(tstname);
    }

}
