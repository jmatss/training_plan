package com.gildedrose;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

class GildedRoseTest {
    @Test
    public void TestSulfurasAlwaysHasQuality80() {
        // ARRANGE
        int sellIn = 0;
        int expectedQuality = 80;

        Item actualItem = new Item(GildedRose.SULFURAS, sellIn, expectedQuality);
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
        int sellIn = 1;
        int initQuality = 5;
        int expectedQuality = initQuality + 1;

        Item actualItem = new Item(GildedRose.AGED_BRIE, sellIn, initQuality);
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
        int sellIn = 0;
        int initQuality = 5;
        int expectedQuality = initQuality + 2;

        Item actualItem = new Item(GildedRose.AGED_BRIE, sellIn, initQuality);
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
        int sellIn = 1;
        int initQuality = 50;
        int expectedQuality = initQuality;

        Item actualItem = new Item(GildedRose.AGED_BRIE, sellIn, initQuality);
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
        int sellIn = 11;
        int initQuality = 0;
        int expectedQuality = initQuality + 1;

        Item actualItem = new Item(GildedRose.BACKSTAGE, sellIn, initQuality);
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
        int sellIn = 10;
        int initQuality = 0;
        int expectedQuality = initQuality + 2;

        Item actualItem = new Item(GildedRose.BACKSTAGE, sellIn, initQuality);
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
        int sellIn = 5;
        int initQuality = 0;
        int expectedQuality = initQuality + 3;

        Item actualItem = new Item(GildedRose.BACKSTAGE, sellIn, initQuality);
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
        int sellIn = 0;
        int initQuality = 5;
        int expectedQuality = 0;

        Item actualItem = new Item(GildedRose.BACKSTAGE, sellIn, initQuality);
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
        int sellIn = 1;
        int initQuality = 50;
        int expectedQuality = initQuality;

        Item actualItem = new Item(GildedRose.BACKSTAGE, sellIn, initQuality);
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
        int sellIn = 1;
        int initQuality = 5;
        int expectedQuality = initQuality - 2;

        Item actualItem = new Item(GildedRose.CONJURED, sellIn, initQuality);
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
        int sellIn = 0;
        int initQuality = 5;
        int expectedQuality = initQuality - 4;

        Item actualItem = new Item(GildedRose.CONJURED, sellIn, initQuality);
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
        int sellIn = 1;
        int initQuality = 0;
        int expectedQuality = initQuality;

        Item actualItem = new Item(GildedRose.CONJURED, sellIn, initQuality);
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
        int sellIn = 1;
        int initQuality = 5;
        int expectedQuality = initQuality - 1;

        Item actualItem = new Item("NORMAL ITEM", sellIn, initQuality);
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
        int sellIn = 0;
        int initQuality = 5;
        int expectedQuality = initQuality - 2;

        Item actualItem = new Item("NORMAL ITEM", sellIn, initQuality);
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
        int sellIn = 1;
        int initQuality = 0;
        int expectedQuality = initQuality;

        Item actualItem = new Item("NORMAL ITEM", sellIn, initQuality);
        Item[] items = { actualItem };
        GildedRose app = new GildedRose(items);

        // ACT
        app.updateQuality();

        // ASSERT
        assertEquals(expectedQuality, actualItem.quality);
    }
}
