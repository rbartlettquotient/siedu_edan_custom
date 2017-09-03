<?php

//dpm($variables);
//$title = array_key_exists('title', $content) ? $content['title'] : '';
?>
<div class="edan-record--location">

  <div class="l-region--hero pane-page-header">
    <div class="l-container">
      <h1 class="page-title"><?php print $content['title']; ?></h1>
    </div>
  </div>
  <div class="l-container layout wrapper-si-unit">
    <?php if($edit_link): ?>
      <div class="edit-link"><?php echo $edit_link;?></div>
    <?php endif; ?>

        <?php if ($rendered_image): ?>
          <div class="col col-sm-4">
            <?php echo $rendered_image; ?>
          </div>
        <?php endif; ?>
        <div class="col <?php echo $rendered_image ? 'col-sm-8 last' : ''?>">
          <p class="si-unit-url"><?php echo $content['record_link'] ?></p>
          <div class="description"><p><?php echo $content['description'] ?></p></div>
          <div class="locations spacing">
           <!-- <?php
            // SI-Unit Locations
            foreach ($locations as $loc): ?>

              <div class="cf beta">
                <a href="<?php echo $loc['#record_link']; ?>">
                  <?php if (isset($loc['grouped_media']['icon'][0])): ?>
                    <span class="field--type-image">
                      <img src="<?php echo $loc['grouped_media']['icon'][0]['content'] ?>" />

                    </span>
                  <?php endif; ?>
                  <span class="title"><?php echo $loc['title']; ?></span>
                  </a>
              </div>

            <?php endforeach; ?>
          -->
          </div>

        </div>
      </div>




      <?php
      //Object Group. Currently not in use on this page.
      if(isset($content['objectGroup'])): ?>
        <div class="museum-object-group">
          <div class="ogmt-og-content">
            <?php if(isset($content['objectGroup']['objectGroupImageUri'])) {
              echo('<img src="'. $content['objectGroup']['objectGroupImageUri']) . '" style="max-width:100%;" />';
            } ?>
          </div>

          <?php if(isset($content['objectGroup']['menu'])): ?>
            <div class="ogmt-og-menu"><?php //@todo not sure you want to show the object group pages here, might add confusion echo $content['objectGroup']['menu']; ?></div>
          <?php endif; ?>

          <?php if (isset($content['objectGroup']['search_results'])): ?>
            <div>
              <?php echo $content['objectGroup']['search_results']; ?>
            </div>
          <?php endif; ?>
        </div>
      <?php endif; ?>





</div>
