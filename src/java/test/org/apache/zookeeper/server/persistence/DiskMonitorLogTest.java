package org.apache.zookeeper.server.persistence;

import org.junit.Assert;
import org.junit.Ignore;
import org.junit.Test;

import static org.junit.Assert.*;

public class DiskMonitorLogTest {

    @Ignore
    public void wakeMeUp() {
        DiskMonitorLog diskMonitorLog = DiskMonitorLog.getInstance();
        if (!diskMonitorLog.isStarted()) {
            diskMonitorLog.start();
        }
        try {
            for (int i=0; i<2; i++) {
                diskMonitorLog.wakeMeUp();
                Thread.sleep(60 *1000);
            }
        } catch (InterruptedException e) {
            Assert.fail(e.getMessage());
        }
        Assert.assertTrue(true);
    }
}