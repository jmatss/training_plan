package com.gildedrose;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class GildedRoseTest {
    @Test
    public void TestSulfurasAlwaysHasQuality80() {
        // ARRANGE
        int expectedQuality = 80;

        Item actualItem = new Item(GildedRose.SULFURAS, 0, expectedQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestAgedBrieIncresesQualityByOneWhenSellInIsPositive() {
        // ARRANGE
        int initQuality = 5;
        int expectedQuality = initQuality + 1;

        Item actualItem = new Item(GildedRose.AGED_BRIE, 1, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestAgedBrieIncresesQualityByTwoWhenSellInIsNegativeOrZero() {
        // ARRANGE
        int initQuality = 5;
        int expectedQuality = initQuality + 2;

        Item actualItem = new Item(GildedRose.AGED_BRIE, 0, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestAgedBrieNeverIncresesQualityOver50() {
        // ARRANGE
        int initQuality = 50;
        int expectedQuality = initQuality;

        Item actualItem = new Item(GildedRose.AGED_BRIE, 1, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestBackstageIncresesQualityByOneWhenSellInIsOver10() {
        // ARRANGE
        int initQuality = 0;
        int expectedQuality = initQuality + 1;

        Item actualItem = new Item(GildedRose.BACKSTAGE, 11, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestBackstageIncresesQualityByTwoWhenSellInIsBetween6And10() {
        // ARRANGE
        int initQuality = 0;
        int expectedQuality = initQuality + 2;

        Item actualItem = new Item(GildedRose.BACKSTAGE, 10, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestBackstageIncresesQualityByThreeWhenSellInIsBetween1And5() {
        // ARRANGE
        int initQuality = 0;
        int expectedQuality = initQuality + 3;

        Item actualItem = new Item(GildedRose.BACKSTAGE, 5, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestBackstageDropsQualityToZeroWhenSellInIsZero() {
        // ARRANGE
        int initQuality = 5;
        int expectedQuality = 0;

        Item actualItem = new Item(GildedRose.BACKSTAGE, 0, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestBackstageNeverIncresesQualityOver50() {
        // ARRANGE
        int initQuality = 50;
        int expectedQuality = initQuality;

        Item actualItem = new Item(GildedRose.BACKSTAGE, 1, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestConjuredDecreasesQualityByTwoWhenSellInIsPositive() {
        // ARRANGE
        int initQuality = 5;
        int expectedQuality = initQuality - 2;

        Item actualItem = new Item(GildedRose.CONJURED, 1, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestConjuredDecreasesQualityByFourWhenSellInIsNegativeOrZero() {
        // ARRANGE
        int initQuality = 5;
        int expectedQuality = initQuality - 4;

        Item actualItem = new Item(GildedRose.CONJURED, 0, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestConjuredNeverDecreasesQualityUnderZero() {
        // ARRANGE
        int initQuality = 0;
        int expectedQuality = initQuality;

        Item actualItem = new Item(GildedRose.CONJURED, 1, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestNormalItemDecreasesQualityByOnwWhenSellInIsPositive() {
        // ARRANGE
        int initQuality = 5;
        int expectedQuality = initQuality - 1;

        Item actualItem = new Item("NORMAL ITEM", 1, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestNormalItemDecreasesQualityByTwoWhenSellInIsNegativeOrZero() {
        // ARRANGE
        int initQuality = 5;
        int expectedQuality = initQuality - 2;

        Item actualItem = new Item("NORMAL ITEM", 0, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }

    @Test
    public void TestNormalItemNeverDecreasesQualityUnderZero() {
        // ARRANGE
        int initQuality = 0;
        int expectedQuality = initQuality;

        Item actualItem = new Item("NORMAL ITEM", 1, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }
}
